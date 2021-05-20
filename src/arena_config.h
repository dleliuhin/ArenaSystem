/*! \file arena_config.h
 * \brief ArenaConfig class interface.
 *
 * \authors Dmitrii Leliuhin, Ilya Batalev
 * \date March 2021
 */

//=======================================================================================

#pragma once

#include <string>

//=======================================================================================
//! \brief Arena Configuration parameters.
struct ArenaConfig final
{
    struct
    {
        //!> Serial number
        std::string sn;

        //!> Firmware version
        std::string firmware;
    } device;

    //-----------------------------------------------------------------------------------

    struct
    {
        struct
        {
            //!> IP address as string
            std::string ip;

            //!> Subnet Mask as string
            std::string mask;

            //!> Gateway as string
            std::string gw;

        } as_str;

        struct
        {
            //!> IP address as int
            uint64_t ip {0};

            //!> Subnet Mask as int
            uint64_t mask {0};

            //!> Gateway as int
            uint64_t gw {0};

        } as_int;

    } network;
};
//=======================================================================================
