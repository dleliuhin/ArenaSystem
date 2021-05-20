/*! \file arena_system.cpp
 * \brief ArenaSystem class implementation.
 *
 * \authors Dmitrii Leliuhin, Ilya Batalev
 * \date March 2021
 */

//=======================================================================================

#include "arena_system.h"

#include <iomanip>

//=======================================================================================

using namespace GenICam;
using namespace GenApi;
using namespace Arena;
using namespace std;

//=======================================================================================

Arena::ISystem* ArenaSystemBase::isystem { nullptr };
ArenaSystem* ArenaSystem::_arena { new ArenaSystem };

//=======================================================================================
ArenaSystemBase::~ArenaSystemBase()
{
    ArenaSystem::close();
}
//=======================================================================================
bool ArenaSystemBase::check()
{
    return isystem != nullptr;
}
//=======================================================================================
bool ArenaSystemBase::update()
{
    if ( !check() ) return false;

    static constexpr uint64_t update_timeout { 10 };

    return isystem->UpdateDevices( update_timeout );
}
//=======================================================================================


//=======================================================================================
void ArenaSystemBase::print_nodes( GenApi::INode* node, const size_t& depth )
{
    if ( node == nullptr ) return;

    // Retrieve display name
    const auto display_name = node->GetDisplayName();

    // Retrieve accessibility
    const auto access_mode = node->GetAccessMode();
    const auto access_mode_str = EAccessModeClass::ToString( access_mode );

    // Retrieve visibility
    const auto visibility = node->GetVisibility();
    const auto visibility_str = EVisibilityClass::ToString( visibility );

    // Retrieve interface type
    const auto interface_type = node->GetPrincipalInterfaceType();
    const auto interface_type_str = EInterfaceTypeClass::ToString( interface_type );

    // Retrieve value
    gcstring value { "-" };

    if ( IsReadable( node ) )
    {
        CValuePtr value_ptr = node;
        value = value_ptr->ToString();
    }

    // Print node information

    cout << string( depth * 2, ' ' ) << display_name
         << setw( 50 - display_name.size() - ( depth * 2 ) ) << " ";
    cout << access_mode_str << setw(5) << " ";
    cout << visibility_str << setw( 14 - visibility_str.size() ) << " ";
    cout << interface_type_str << setw( 20 - interface_type_str.size() ) << " ";
    cout << ( value.size() < 50 ? value : "..." );
    cout << "\n";

    // Explore category node children

    CCategoryPtr category = node;

    // Continue traverse tree

    if ( category )
    {
        FeatureList_t children;
        category->GetFeatures( children );

        for ( auto* c : children ) print_nodes( c->GetNode(), depth + 1 );
    }
}
//=======================================================================================


//=======================================================================================
ArenaSystem::~ArenaSystem()
{
    close();
    if ( _arena != nullptr ) delete _arena;
}
//=======================================================================================
bool ArenaSystem::open()
{
    if ( !check() )
    {
        isystem = OpenSystem();
        cout << "Arena SDK initialized!";
    }

    const bool ok = update();

    return check() && ok;
}
//=======================================================================================
bool ArenaSystem::close()
{
    if ( check() )
    {
        CloseSystem( isystem );
        isystem = nullptr;
        cout << "Arena SDK deinitialized!";
    }

    return !check();
}
//=======================================================================================
IDevice * ArenaSystem::create( const ArenaConfig& conf )
{
    auto info = exist( conf, true );

    if ( !info ) return nullptr;

    // Check Firmware version

    if ( info->DeviceVersion().c_str() != conf.device.firmware )
    {
        cout << "Incompatible firmware versions."
                 << " | Expected ver. : " << conf.device.firmware
                 << " | Device ver. : " << info->DeviceVersion();
        return nullptr;
    }

    // Check if device opened

    try
    {
        return isystem->CreateDevice( *info );
    }
    catch ( const GenICam_3_0::AccessException& e )
    {
        std::cerr << "Device already opened!" << e.what();
        exit( EXIT_FAILURE );
    }
}
//=======================================================================================
bool ArenaSystem::destroy( IDevice* device )
{
    if ( device == nullptr )
    {
        std::cout << "Device already destroyed or not initialized!";
        return true;
    }

    if ( !ArenaSystem::check() )
    {
        std::cout << "Unable to delete device! ArenaSystemBase::isystem is nullptr!"
                 << "Memory leak from -> " << device;
        return false;
    }

    isystem->DestroyDevice( device );

    // Message from Lucid Technical support:
    // "Also, I'll bring up your suggestion about nullptr with our Software team."
    // In the next update, the Lucid's developers will fix this bug in ArenaSDK.
    device = nullptr;

    return true;
}
//=======================================================================================
bool ArenaSystem::force_ip( const ArenaConfig& conf )
{
    auto info = exist( conf );

    if ( !info ) return false;

    // Check if network parameters is equal with configuration file

    if ( info->SerialNumber().c_str() == conf.device.sn &&
         info->IpAddress() == conf.network.as_int.ip &&
         info->SubnetMask() == conf.network.as_int.mask &&
         info->DefaultGateway() == conf.network.as_int.gw )
        return true;

    isystem->ForceIp( info->MacAddress(),
                      conf.network.as_int.ip,
                      conf.network.as_int.mask,
                      conf.network.as_int.gw );

    return update();
}
//=======================================================================================
unique_ptr<DeviceInfo> ArenaSystem::exist( const ArenaConfig& conf, const bool add )
{
    // 1. Device serial number empty
    // 2. Need additional check and one of network parameters is empty
    if ( conf.device.sn.empty() ||
         ( add && ( conf.network.as_str.ip.empty() ||
                    conf.network.as_str.mask.empty() ||
                    conf.network.as_str.gw.empty() ) ) )
    {
        std::cout << "Please, specify networking parameters in configuration file!";
        return nullptr;
    }

    if ( !update() )
    {
        std::cout << "Device list not updated!";
        return nullptr;
    }

    //-----------------------------------------------------------------------------------

    auto devices = info();

    if ( devices.empty() ) return nullptr;

    //-----------------------------------------------------------------------------------

    auto device_iter = find_if( devices.begin(), devices.end(),
                                [ &conf, &add ]( DeviceInfo& device )->bool
    {
        bool res = device.SerialNumber().c_str() == conf.device.sn;

        // Extra check if network parameters is equal with configuration as int
        if ( add ) res &= device.IpAddress() == conf.network.as_int.ip &&
                          device.SubnetMask() == conf.network.as_int.mask &&
                          device.DefaultGateway() == conf.network.as_int.gw;
        return res;
    } );

    if ( device_iter == devices.end() ) return nullptr;

    return make_unique<DeviceInfo>( *device_iter );
}
//=======================================================================================
