//==================================================================
//
//カメラ処理 [camera.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "3Dplayer.h"

//================================================
//コンストラクタ
//================================================
CCamera::CCamera()
{

}

//================================================
//デストラクタ
//================================================
CCamera::~CCamera()
{
}

//================================================
//初期化処理
//================================================
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, -2.50f, 0.0f);

	float fDisX = m_posV.x - m_posR.x;
	float fDisZ = m_posV.z - m_posR.z;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}


	m_Distance = sqrtf((fDisX * fDisX) + (fDisZ * fDisZ));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CCamera::Uninit(void)
{
}

//================================================
//更新処理
//================================================
void CCamera::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//プレイヤーの取得
	C3DPlayer* p3DPlayer = CManager::Get3DPlayer();

	if (!p3DPlayer) return;

	D3DXVECTOR3 playerPos = p3DPlayer->GetPos();

	// プレイヤーの少し後ろ上から見る
	m_posR = playerPos + D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	m_posV = playerPos + D3DXVECTOR3(0.0f, 100.0f, -200.0f);

	//カメラの移動
	if (pInputKeyboard->Repeat(DIK_W) == true)
	{
		m_posR.x += sinf(m_rot.y) * -2.0f;
		m_posR.z += cosf(m_rot.y) * -2.0f;

	}
	else if (pInputKeyboard->Repeat(DIK_A) == true)
	{
		m_posR.x += sinf(D3DX_PI * 0.5f + m_rot.y) * 2.0f;
		m_posR.z += cosf(D3DX_PI * 0.5f + m_rot.y) * 2.0f;

	}
	else if (pInputKeyboard->Repeat(DIK_S) == true)
	{
		m_posR.x += sinf(m_rot.y) * 2.0f;
		m_posR.z += cosf(m_rot.y) * 2.0f;

	}
	else if (pInputKeyboard->Repeat(DIK_D) == true)
	{
		m_posR.x += sinf(D3DX_PI * 0.5f + m_rot.y) * -2.0f;
		m_posR.z += cosf(D3DX_PI * 0.5f + m_rot.y) * -2.0f;

	}

	//注視点の旋回
	if (pInputKeyboard->Repeat(DIK_X) == true)
	{
		m_rot.y += 0.01f;
		m_posR.x += sinf(D3DX_PI * 0.5f + m_rot.y) * 2.0f;
		m_posR.z += cosf(D3DX_PI * 0.5f + m_rot.y) * 2.0f;

		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2;
		}
	}
	else if (pInputKeyboard->Repeat(DIK_Z) == true)
	{
		m_rot.y -= 0.01f;
		m_posR.x += sinf(D3DX_PI * 0.5f + m_rot.y) * -2.0f;
		m_posR.z += cosf(D3DX_PI * 0.5f + m_rot.y) * -2.0f;

		if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2;
		}
	}

	//視点の旋回
	if (pInputKeyboard->Repeat(DIK_V) == true)
	{
		m_rot.y += 0.01f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2;
		}
	}
	else if (pInputKeyboard->Repeat(DIK_C) == true)
	{
		m_rot.y -= 0.01f;
		if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2;
		}
	}

	//視点の旋回
	if (pInputKeyboard->Repeat(DIK_J) == true)
	{
		m_rot.x += 0.01f;
		if (m_rot.x > D3DX_PI)
		{
			m_rot.x -= D3DX_PI * 2;
		}
	}
	else if (pInputKeyboard->Repeat(DIK_K) == true)
	{
		m_rot.x -= 0.01f;
		if (m_rot.x < D3DX_PI)
		{
			m_rot.x += D3DX_PI * 2;
		}
	}

	//注視点の旋回
	if (pInputKeyboard->Repeat(DIK_Q) == true)
	{
		m_rot.z += 0.01f;
		m_posR.y += sinf(D3DX_PI * 0.5f + m_rot.y) * 2.0f;
		m_posR.x += cosf(D3DX_PI * 0.5f + m_rot.y) * 2.0f;

		if (m_rot.z > D3DX_PI)
		{
			m_rot.z -= D3DX_PI * 2;
		}

	}
	else if (pInputKeyboard->Repeat(DIK_E) == true)
	{
		m_rot.z -= 0.01f;
		m_posR.y += sinf(D3DX_PI * 0.5f + m_rot.y) * -2.0f;
		m_posR.x += cosf(D3DX_PI * 0.5f + m_rot.y) * -2.0f;

		if (m_rot.z < -D3DX_PI)
		{
			m_rot.z += D3DX_PI * 2;
		}

	}


	//角度の正規化
	m_posV.x = m_posR.x + cosf(m_rot.x) * sinf(m_rot.y) * m_Distance;
	m_posV.y = m_posR.y + sinf(m_rot.x) * m_Distance;
	m_posV.z = m_posR.z + cosf(m_rot.x) * cosf(m_rot.y) * m_Distance;
}

//================================================
//カメラ設定処理
//================================================
void CCamera::SetCamera(void)
{
	//pDeviceの取得
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
