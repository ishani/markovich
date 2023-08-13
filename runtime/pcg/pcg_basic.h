/*
 * PCG Random Number Generation for C.
 *
 * Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * For additional information about the PCG random number generation scheme,
 * including its license and other licensing options, visit
 *
 *     http://www.pcg-random.org
 */

#pragma once

#include <inttypes.h>


#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4146 )
#endif 

struct pcg32_random_t
{
    constexpr pcg32_random_t( uint64_t _state, uint64_t _inc )
      : state(_state)
      , inc(_inc)
    {}

    uint64_t state;             // RNG state.  All values are possible.
    uint64_t inc;               // Controls which RNG sequence (stream) is
                                // selected. Must *always* be odd.
};

// pcg32_random_u32( state )
//     Generate a uniformly distributed 32-bit random number

constexpr uint32_t
pcg32_random_u32( pcg32_random_t& rng )
{
    const uint64_t oldstate     = rng.state;
                      rng.state = oldstate * 6364136223846793005ULL + rng.inc;
    const uint32_t xorshifted   = (uint32_t)( ((oldstate >> 18u) ^ oldstate) >> 27u );
    const uint32_t rot          = (uint32_t)( oldstate >> 59u );

    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}


constexpr float
pcg32_random_float( pcg32_random_t& rng )
{
    // mask lower 23 bits, multiply by 1/2**23.
    return (pcg32_random_u32(rng) & ((1 << 23) - 1)) * 0.00000011920928955078125f;
}

// pcg32_seed( initstate, initseq ) -> state
//     Seed the rng.  Specified in two parts, state initializer and a
//     sequence selection constant (a.k.a. stream id)

constexpr pcg32_random_t
pcg32_seed( const uint64_t initstate, const uint64_t initseq )
{
    pcg32_random_t rng( 0U, (initseq << 1u) | 1u );
    pcg32_random_u32( rng );
    rng.state += initstate;
    pcg32_random_u32( rng );
    return rng;
}


// pcg32_random_u32_range( state, bound ):
//     Generate a uniformly distributed number, r, where 0 <= r < bound

constexpr uint32_t
pcg32_random_u32_range( pcg32_random_t& rng, const uint32_t bound )
{
    // To avoid bias, we need to make the range of the RNG a multiple of
    // bound, which we do by dropping output less than a threshold.
    // A naive scheme to calculate the threshold would be to do
    //
    //     uint32_t threshold = 0x100000000ull % bound;
    //
    // but 64-bit div/mod is slower than 32-bit div/mod (especially on
    // 32-bit platforms).  In essence, we do
    //
    //     uint32_t threshold = (0x100000000ull-bound) % bound;
    //
    // because this version will calculate the same modulus, but the LHS
    // value is less than 2^32.

    uint32_t threshold = -bound % bound;

    // Uniformity guarantees that this loop will terminate.  In practice, it
    // should usually terminate quickly; on average (assuming all bounds are
    // equally likely), 82.25% of the time, we can expect it to require just
    // one iteration.  In the worst case, someone passes a bound of 2^31 + 1
    // (i.e., 2147483649), which invalidates almost 50% of the range.  In
    // practice, bounds are typically small and only a tiny amount of the range
    // is eliminated.
    for( ;; ) {
        uint32_t r = pcg32_random_u32( rng );
        if( r >= threshold )
            return r % bound;
    }
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif 
