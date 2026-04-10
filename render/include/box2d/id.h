// SPDX-FileCopyrightText: 2023 Erin Catto
// SPDX-License-Identifier: MIT

#pragma once

#include "base.h"

#include <stdint.h>

typedef struct b2WorldId
{
    uint16_t index1;
    uint16_t generation;
} b2WorldId;

typedef struct b2BodyId
{
    int32_t index1;
    uint16_t world0;
    uint16_t generation;
} b2BodyId;

typedef struct b2ShapeId
{
    int32_t index1;
    uint16_t world0;
    uint16_t generation;
} b2ShapeId;

typedef struct b2ChainId
{
    int32_t index1;
    uint16_t world0;
    uint16_t generation;
} b2ChainId;

typedef struct b2JointId
{
    int32_t index1;
    uint16_t world0;
    uint16_t generation;
} b2JointId;

static const b2WorldId b2_nullWorldId = B2_ZERO_INIT;
static const b2BodyId b2_nullBodyId = B2_ZERO_INIT;
static const b2ShapeId b2_nullShapeId = B2_ZERO_INIT;
static const b2ChainId b2_nullChainId = B2_ZERO_INIT;
static const b2JointId b2_nullJointId = B2_ZERO_INIT;

#define B2_IS_NULL( id ) ( id.index1 == 0 )

#define B2_IS_NON_NULL( id ) ( id.index1 != 0 )

#define B2_ID_EQUALS( id1, id2 ) ( id1.index1 == id2.index1 && id1.world0 == id2.world0 && id1.generation == id2.generation )

B2_INLINE uint64_t b2StoreBodyId( b2BodyId id )
{
    return ( (uint64_t)id.index1 << 32 ) | ( (uint64_t)id.world0 ) << 16 | (uint64_t)id.generation;
}

B2_INLINE b2BodyId b2LoadBodyId( uint64_t x )
{
    b2BodyId id = { (int32_t)( x >> 32 ), (uint16_t)( x >> 16 ), (uint16_t)( x ) };
    return id;
}

B2_INLINE uint64_t b2StoreShapeId( b2ShapeId id )
{
    return ( (uint64_t)id.index1 << 32 ) | ( (uint64_t)id.world0 ) << 16 | (uint64_t)id.generation;
}

B2_INLINE b2ShapeId b2LoadShapeId( uint64_t x )
{
    b2ShapeId id = { (int32_t)( x >> 32 ), (uint16_t)( x >> 16 ), (uint16_t)( x ) };
    return id;
}

B2_INLINE uint64_t b2StoreChainId( b2ChainId id )
{
    return ( (uint64_t)id.index1 << 32 ) | ( (uint64_t)id.world0 ) << 16 | (uint64_t)id.generation;
}

B2_INLINE b2ChainId b2LoadChainId( uint64_t x )
{
    b2ChainId id = { (int32_t)( x >> 32 ), (uint16_t)( x >> 16 ), (uint16_t)( x ) };
    return id;
}

B2_INLINE uint64_t b2StoreJointId( b2JointId id )
{
    return ( (uint64_t)id.index1 << 32 ) | ( (uint64_t)id.world0 ) << 16 | (uint64_t)id.generation;
}

B2_INLINE b2JointId b2LoadJointId( uint64_t x )
{
    b2JointId id = { (int32_t)( x >> 32 ), (uint16_t)( x >> 16 ), (uint16_t)( x ) };
    return id;
}