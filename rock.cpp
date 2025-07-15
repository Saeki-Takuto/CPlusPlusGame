//==================================================================
//
//�Ώ��� [rock.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "rock.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ�
//================================================
D3DXVECTOR3 CRock::m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CRock::m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CRock::m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

LPD3DXMESH CRock::m_pMesh = NULL;
LPD3DXBUFFER CRock::m_pBuffMat = NULL;
DWORD CRock::m_dwNumMat = NULL;

//================================================
//�R���X�g���N�^
//================================================
CRock::CRock()
{
}

//================================================
//�f�X�g���N�^
//================================================
CRock::~CRock()
{
}

//================================================
//����������
//================================================
HRESULT CRock::Init(void)
{
	CObjectX::Init();

	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	nNumVtx = m_pMesh->GetNumVertices();
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//x�̍ŏ��l��r
		if (vtx.x < m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}

		//x�̍ő�l��r
		if (vtx.x > m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}

		//y�̍ŏ��l��r
		if (vtx.y < m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}

		//y�̍ő�l��r
		if (vtx.y > m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}

		//z�̍ŏ��l��r
		if (vtx.z < m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}

		//z�̍ő�l��r
		if (vtx.z > m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();

	m_size = m_vtxMax - m_vtxMin;

	return S_OK;
}

//================================================
//�I������
//================================================
void CRock::Uninit(void)
{
	CObjectX::Uninit();
}

//================================================
//�X�V����
//================================================
void CRock::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CRock::Draw(void)
{
	CObjectX::Draw();
}

//================================================
//��������
//================================================
CRock* CRock::Create(float X, float Y, float Z)
{
	CRock* pRock = new CRock();
	pRock->BindX(m_pBuffMat, m_dwNumMat, m_pMesh);
	pRock->Init();
	pRock->SetPos(X, Y, Z);
	return pRock;
}

//================================================
//�e�N�X�`�����[�h����
//================================================
HRESULT CRock::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	HRESULT hr = D3DXLoadMeshFromX("data/MODEL/privacy.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	if (FAILED(hr))
	{
		m_pMesh = NULL;
		m_pBuffMat = NULL;
		m_dwNumMat = 0;
		return E_FAIL;
	}

	return S_OK;
}

//================================================
//�e�N�X�`���A�����[�h����
//================================================
void CRock::Unload(void)
{
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	if (m_dwNumMat != NULL)
	{
		//m_dwNumMat->Release();
		m_dwNumMat = NULL;
	}

	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
}

//================================================
//�΂̍����擾����
//================================================
float CRock::GetHeight(float posx, float posz)
{
	D3DXVECTOR3 rockPos = GetPos();

	float minX = rockPos.x + m_vtxMin.x;
	float maxX = rockPos.x + m_vtxMax.x;
	float minZ = rockPos.z + m_vtxMin.z;
	float maxZ = rockPos.z + m_vtxMax.z;
	float topY = rockPos.y + m_vtxMax.y;

	if (posx >= minX && posx <= maxX &&
		posz >= minZ && posz <= maxZ)
	{
		return topY;
	}

	return -1.0f;
}
