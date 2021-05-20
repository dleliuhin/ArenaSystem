/*! \file arena_system_base.h
 * \brief ArenaSystemBase class interface.
 *
 * \authors Dmitrii Leliuhin, Ilya Batalev
 * \date March 2021
 */

//=======================================================================================

#pragma once

#include "ArenaApi.h"

#include <exception>

//=======================================================================================
namespace Arena
{

using Devices    = std::vector<DeviceInfo>;
using Interfaces = std::vector<InterfaceInfo>;

} // namespace Arena
//=======================================================================================


//=======================================================================================
//! \brief The ArenaSystemBase class
class ArenaSystemBase
{
public:

    //! \default
    explicit ArenaSystemBase() = default;

    //! \brief Deletes ArenaSystemBase::isystem
    virtual ~ArenaSystemBase();

    //-----------------------------------------------------------------------------------

    /*!
     * \brief Check if isystem object is !nullptr
     * \return nullptr ? false : true
     */
    static bool check();

    /*!
     * \brief Updates the internal list of devices
     * \return true if updated
     */
    static bool update();

    //-----------------------------------------------------------------------------------

    /*!
     * \brief Get Devices/Iterfaces list
     * \tparam T Vector of Arena::DeviceInfo or Arena::InterfaceInfo
     * \tparam TE Flag if need throw error if no devices/interfaces was found
     */
    template <class T = Arena::Devices, bool TE = false>
    static T info();

    //-----------------------------------------------------------------------------------

    /*!
     * \brief Trace info of all Devices/Iterfaces list
     * \tparam Arena::Arena::DeviceInfo/IterfaceInfo list
     */
    template <class T = Arena::Devices>
    static void print();

    /*!
     * \brief Trace info of specific Arena::DeviceInfo/IterfaceInfo
     * \tparam Arena::DeviceInfo/IterfaceInfo
     */
    template <class T = Arena::DeviceInfo>
    static void print_one( T* info );

    /*!
     * \brief print_nodes Trace info of node and node's childrens recursively
     * \param node Target node
     * \param depth For traverse elements
     */
    static void print_nodes( GenApi::INode* node, const size_t& depth = 0 );

    //-----------------------------------------------------------------------------------

protected:

    //!> Pointer to the system object interface
    static Arena::ISystem *isystem;

};
//=======================================================================================


//=======================================================================================
template <class T, bool TE>
T ArenaSystemBase::info()
{
    if ( !isystem ) throw std::logic_error( "Arena::ArenaSystem not opened!" );

    update();

    T res;

    if constexpr ( std::is_same_v<Arena::Devices, T> )
            res = isystem->GetDevices();

    else if constexpr ( std::is_same_v<Arena::Interfaces, T> )
            res = isystem->GetInterfaces();

    if ( res.empty() )
    {
        std::string msg;

        if constexpr ( std::is_same_v<Arena::Devices, T> )
                msg = "No devices was found";
        else if constexpr ( std::is_same_v<Arena::Interfaces, T> )
                msg = "No interfaces was found";

        if constexpr (TE) throw std::logic_error( msg );
        else std::cout << msg;

        return {};
    }

    //-----------------------------------------------------------------------------------

    // Sort -> Unique -> Erase

    constexpr auto sorter = []( auto& i1, auto& i2 ) -> bool
    {
        if constexpr ( std::is_same_v<Arena::Devices, T> )
                return std::stoi( i1.SerialNumber().c_str() ) < std::stoi( i2.SerialNumber().c_str() );

        else if constexpr ( std::is_same_v<Arena::Interfaces, T> )
                return i1.MacAddress() < i2.MacAddress();
    };

    std::sort( res.begin(), res.end(), sorter );

    constexpr auto unifier = []( auto& i1, auto& i2 ) -> bool
    {
        if constexpr ( std::is_same_v<Arena::Devices, T> )
                return i1.SerialNumber() == i2.SerialNumber();

        else if constexpr ( std::is_same_v<Arena::Interfaces, T> )
                return i1.MacAddress() == i2.MacAddress();
    };

    res.erase( std::unique( res.begin(), res.end(), unifier ), res.end() );

    return res;
}
//=======================================================================================


//=======================================================================================
template<class T>
void ArenaSystemBase::print()
{
    T list;

    if constexpr( std::is_same_v<Arena::Devices, T> )
            list = info<Arena::Devices>();

    else if constexpr ( std::is_same_v<Arena::Interfaces, T> )
            list = info<Arena::Interfaces>();

    if ( list.empty() ) return;

    //-----------------------------------------------------------------------------------

    for ( auto& i: list )
    {
        if constexpr( std::is_same_v<Arena::Devices, T> )
                ArenaSystemBase::print_one(&i);

        else if constexpr ( std::is_same_v<Arena::Interfaces, T> )
                ArenaSystemBase::print_one<Arena::InterfaceInfo>(&i);
    }
}
//=======================================================================================

//=======================================================================================
template<class T>
void ArenaSystemBase::print_one( T* info )
{
    std::cout << "=====================================================================";

    if constexpr( std::is_same_v<Arena::DeviceInfo, T> )
            std::cout << "Connection to device with :"
                   << "Model name :"         << info->ModelName()
                   << " | Vendor name :"     << info->VendorName()
                   << " | Serial number :"   << info->SerialNumber()
                   << " | IP address :"      << info->IpAddressStr()
                   << " | Subnet Mask :"     << info->SubnetMaskStr()
                   << " | Default Gateway :" << info->DefaultGatewayStr()
                   << " | MAC Adress :"      << info->MacAddressStr()
                   << " | User Defined :"    << info->UserDefinedName()
                   << " | Is DHCP? :"        << info->IsDHCPConfigurationEnabled()
                   << " | Is Persistent? :"  << info->IsPersistentIpConfigurationEnabled()
                   << " | Is LLA ? :"        << info->IsLLAConfigurationEnabled()
                   << " | Device Version :"  << info->DeviceVersion();

    else if constexpr ( std::is_same_v<Arena::InterfaceInfo, T> )
            std::cout << "MAC Adress :"     << info->MacAddressStr()
                      << " | IP Adress :"   << info->IpAddressStr()
                      << " | Subnet Mask :" << info->SubnetMaskStr();

    std::cout << "=====================================================================";
}
//=======================================================================================
