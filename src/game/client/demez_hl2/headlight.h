//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef HEADLIGHT_H
#define HEADLIGHT_H
#ifdef _WIN32
#pragma once
#endif

#include "flashlight.h"

class CHeadlightEffect : public CFlashlightEffect
{
public:
	
	CHeadlightEffect();
	~CHeadlightEffect();

	virtual void UpdateLight(const Vector &vecPos, const Vector &vecDir, const Vector &vecRight, const Vector &vecUp, int nDistance);
};



#endif // FLASHLIGHTEFFECT_H
