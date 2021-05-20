/*! \file arena_system.h
 * \brief ArenaSystem class interface.
 *
 * \authors Dmitrii Leliuhin, Ilya Batalev
 * \date March 2021
 */

//=======================================================================================

#pragma once

#include "arena_system_base.h"
#include "arena_config.h"

#include "ArenaApi.h"

#include <vector>

//=======================================================================================

//! \brief Human shell via Singleton pattern for ArenaSDK system commands execution
class ArenaSystem : public ArenaSystemBase
{
public:

    //-----------------------------------------------------------------------------------

    /*! 
     * \brief Initializes the Arena SDK and retrieves the system object.
     * \return true if initialized successfully
     * \warning The system must be closed or memory will leak.
     */
    static bool open();

    /*! 
     * \brief Deinitializes the Arena SDK & clean ups the system
     * \return true if deinitialized successfully
     */
    static bool close();

    //-----------------------------------------------------------------------------------

    /*! 
     * \brief Create device based on configuration file info
     * \param[in] conf Configuration settings
     * \return Pointer to created device
     * \warning Need to destroy after executions by call
     * arena.isystem.DestroyDevice( device ) or arena.close( device )
     */
    static Arena::IDevice * create( const ArenaConfig& conf );

    /*!
     * \brief Close existing device
     * \param[out] device Pointer to existing device
     * \return true if device closed
     * \warning If device not closed -> memory leak
     * \example Is short alternative of arena.isystem.DestroyDevice( device )
     */
    static bool destroy( Arena::IDevice* device );

    /*!
     * \brief Forces the device that matches the Serial Number to new IP, SM and GW
     * \param[in] conf Configuration settings
     * \return true if device network parameters forced
     */
    static bool force_ip( const ArenaConfig& conf );

    /*!
     * \brief Check if exist device by configuration parameters by SN
     * \param[in] conf Configuration settings
     * \param[in] add Flag if need additional check of IP, SM, GW
     * \return Smart pointer with information about existing device
     * \default Check only by device Serial Nymber
     * \warning If device doesn't exist pointer set to nullptr
     */
    static std::unique_ptr<Arena::DeviceInfo> exist( const ArenaConfig& conf,
                                                     const bool add = false );

    //-----------------------------------------------------------------------------------

private:

    //!> For global interaction with ArenaSDK system
    static ArenaSystem* _arena;

    //-----------------------------------------------------------------------------------

    ArenaSystem() = default;
    ArenaSystem( const ArenaSystem& ) = delete;
    ArenaSystem & operator=( const ArenaSystem& )= delete;

    //! \brief Close ISystem object
    ~ArenaSystem() override;

};
//=======================================================================================
