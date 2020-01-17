//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H
#ifdef _WIN32
#pragma once
#endif

class CFlashlightEffect
{
public:

	CFlashlightEffect(int nEntIndex = 0);
	virtual ~CFlashlightEffect();

	void UpdateLight( const Vector& vecPos, const Vector& vecDir, const Vector& vecRight, const Vector& vecUp );

	void TurnOn();
	void TurnOff();
	bool IsOn( void ) { return m_bIsOn;	}

	ClientShadowHandle_t GetFlashlightHandle( void ) { return m_FlashlightHandle; }
	void SetFlashlightHandle( ClientShadowHandle_t Handle ) { m_FlashlightHandle = Handle;	}
	
protected:

	void LightOff();

	bool m_bIsOn;
	int m_nEntIndex;
	ClientShadowHandle_t m_FlashlightHandle;

	float m_flDistMod;

	// Texture for flashlight
	CTextureReference m_FlashlightTexture;
};


#endif // FLASHLIGHTEFFECT_H
