//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//===========================================================================//

#include "cbase.h"
#include "headlight.h"
#include "tier0/vprof.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

extern ConVar r_flashlightdepthres;
extern ConVar r_flashlightdepthtexture;

void r_newflashlightCallback_f( IConVar *pConVar, const char *pOldString, float flOldValue );

//static ConVar r_flashlightlockposition( "r_flashlightlockposition", "0", FCVAR_CHEAT );
static ConVar r_headlight_fov_width( "r_headlight_fov_width", "90.0", FCVAR_CHEAT );
static ConVar r_headlight_fov_height( "r_headlight_fov_height", "90.0", FCVAR_CHEAT );

static ConVar r_headlight_near( "r_headlight_near", "4.0", FCVAR_CHEAT );
static ConVar r_headlight_far( "r_headlight_far", "750.0", FCVAR_CHEAT );

static ConVar r_headlight_constant( "r_headlight_constant", "0.0", FCVAR_CHEAT );
static ConVar r_headlight_linear( "r_headlight_linear", "0.0", FCVAR_CHEAT );
static ConVar r_headlight_quadratic( "r_headlight_quadratic", "10000.0", FCVAR_CHEAT );

static ConVar r_headlight_visualizetrace( "r_headlight_visualizetrace", "0", FCVAR_CHEAT );
static ConVar r_headlight_shadowatten( "r_headlight_shadowatten", "0.35", FCVAR_CHEAT );

static ConVar mat_slopescaledepthbias_shadowmap( "mat_slopescaledepthbias_shadowmap", "16", FCVAR_CHEAT );
static ConVar mat_depthbias_shadowmap(	"mat_depthbias_shadowmap", "0.0005", FCVAR_CHEAT  );

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CHeadlightEffect::CHeadlightEffect() 
{
}

CHeadlightEffect::~CHeadlightEffect()
{
}

// i might be able to base this off of projected texture instead, but meh
// also i need to fix shader issues with this as well
void CHeadlightEffect::UpdateLight( const Vector &vecPos, const Vector &vecDir, const Vector &vecRight, const Vector &vecUp, int nDistance )
{
	if ( IsOn() == false )
		 return;

	VPROF( "CHeadlightEffect::UpdateLight" );

	FlashlightState_t state;
	Vector basisX, basisY, basisZ;
	basisX = vecDir;
	basisY = vecRight;
	basisZ = vecUp;
	VectorNormalize(basisX);
	VectorNormalize(basisY);
	VectorNormalize(basisZ);

	BasisToQuaternion( basisX, basisY, basisZ, state.m_quatOrientation );
		
	state.m_vecLightOrigin = vecPos;

	state.m_fHorizontalFOVDegrees = r_headlight_fov_width.GetFloat();
	state.m_fVerticalFOVDegrees = r_headlight_fov_height.GetFloat();

	state.m_fQuadraticAtten = r_headlight_quadratic.GetFloat();
	state.m_fLinearAtten = r_headlight_linear.GetFloat();
	state.m_fConstantAtten = r_headlight_constant.GetFloat();

	state.m_Color[0] = 1.0f;
	state.m_Color[1] = 1.0f;
	state.m_Color[2] = 1.0f;
	state.m_Color[ 3 ] = 0.0f;

	state.m_NearZ = r_headlight_near.GetFloat();
	state.m_FarZ = r_headlight_far.GetFloat();

	state.m_bEnableShadows = true;
	state.m_pSpotlightTexture = m_FlashlightTexture;
	state.m_nSpotlightTextureFrame = 0;
	
	if( GetFlashlightHandle() == CLIENTSHADOW_INVALID_HANDLE )
	{
		SetFlashlightHandle( g_pClientShadowMgr->CreateFlashlight( state ) );
	}
	else
	{
		g_pClientShadowMgr->UpdateFlashlightState( GetFlashlightHandle(), state );
	}
	
	g_pClientShadowMgr->UpdateProjectedTexture( GetFlashlightHandle(), true );
}

