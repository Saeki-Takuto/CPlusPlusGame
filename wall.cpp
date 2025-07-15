//==================================================================
//
//�Ǐ��� [wall.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//�C���N���[�h
//================================================
#include "wall.h"
#include "renderer.h"
#include "manager.h"

//================================================
//�R���X�g���N�^
//================================================
CWall::CWall()
{
}

//================================================
//�f�X�g���N�^
//================================================
CWall::~CWall()
{
}

//================================================
//����������
//================================================
HRESULT CWall::Init(void)
{
	//�f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WALL.png",
		&m_pTexturePolygon);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPolygon, NULL);

	m_posPolygon.z = 150.0f;
	m_posPolygon.y = 700.0f;

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH, +WALL_HEIGHT,0.0f);
	pVtx[1].pos = D3DXVECTOR3(+WALL_WIDTH, +WALL_HEIGHT,0.0f);
	pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH, -WALL_HEIGHT,0.0f);
	pVtx[3].pos = D3DXVECTOR3(+WALL_WIDTH, -WALL_HEIGHT,0.0f);


	//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(2.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 8.0f);
	pVtx[3].tex = D3DXVECTOR2(2.0f, 8.0f);

	// ���_���W
	D3DXVECTOR3 a = pVtx[0].pos;
	D3DXVECTOR3 b = pVtx[1].pos;
	D3DXVECTOR3 c = pVtx[2].pos;
	D3DXVECTOR3 d = pVtx[3].pos;

	D3DXVECTOR3 n1, n2;

	// �O�p�`1: a, b, c
	D3DXVECTOR3 vec1 = b - a;
	D3DXVECTOR3 vec2 = c - a;
	D3DXVec3Cross(&n1, &vec1, &vec2);
	D3DXVec3Normalize(&n1, &n1);

	// �O�p�`2: b, d, c
	D3DXVECTOR3 v3 = d - b;
	D3DXVECTOR3 v4 = c - b;
	D3DXVec3Cross(&n2, &v3, &v4);
	D3DXVec3Normalize(&n2, &n2);

	// �e���_�̖@���i���ω��j
	pVtx[0].nor = n1;
	pVtx[1].nor = D3DXVECTOR3((n1.x + n2.x) / 2, (n1.y + n2.y) / 2, (n1.z + n2.z) / 2);
	D3DXVec3Normalize(&pVtx[1].nor, &pVtx[1].nor);
	pVtx[2].nor = D3DXVECTOR3((n1.x + n2.x) / 2, (n1.y + n2.y) / 2, (n1.z + n2.z) / 2);
	D3DXVec3Normalize(&pVtx[2].nor, &pVtx[2].nor);
	pVtx[3].nor = n2;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffPolygon->Unlock();

	return S_OK;
}

//================================================
//�I������
//================================================
void CWall::Uninit(void)
{
	if (m_pVtxBuffPolygon != NULL)
	{
		m_pVtxBuffPolygon->Release();
		m_pVtxBuffPolygon = NULL;
	}

	if (m_pTexturePolygon != NULL)
	{
		m_pTexturePolygon->Release();
		m_pTexturePolygon = NULL;
	}
}

//================================================
//�X�V����
//================================================
void CWall::Update(void)
{
	//CInputKeyboard* pInputKeyboard;
	//pInputKeyboard = CManager::GetInputKeyboard();

	//if (pInputKeyboard->Repeat(DIK_5) == true)
	//{
	//	m_posPolygon.x += 10.0f;
	//}

	//VERTEX_3D* pVtx = NULL;
	////���_�o�b�t�@�����b�N
	//m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W��ݒ�
	//pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH, +WALL_HEIGHT, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(+WALL_WIDTH, +WALL_HEIGHT, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH, -WALL_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(+WALL_WIDTH, -WALL_HEIGHT, 0.0f);

	////�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	//pVtx[0].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[1].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[2].nor = D3DXVECTOR3(0.0, 1.0, 0.0);
	//pVtx[3].nor = D3DXVECTOR3(0.0, 1.0, 0.0);

	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//////�e�N�X�`�����W�̐ݒ�
	////pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	////pVtx[1].tex = D3DXVECTOR2(5.0f, 0.0f);
	////pVtx[2].tex = D3DXVECTOR2(0.0f, 5.0f);
	////pVtx[3].tex = D3DXVECTOR2(5.0f, 5.0f);

	////���_�o�b�t�@�̃A�����b�N
	//m_pVtxBuffPolygon->Unlock();


}

//================================================
//�`�揈��
//================================================
void CWall::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = renderer->GetDevice();

	// ���C�e�B���O�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �f�B���N�V���i�����C�g�ݒ�
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	light.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1);
	pDevice->SetLight(0, &light);
	pDevice->LightEnable(0, TRUE);

	// �}�e���A���ݒ�
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	mtrl.Ambient = D3DXCOLOR(1, 1, 1, 1);
	pDevice->SetMaterial(&mtrl);

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldPolygon);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotPolygon.y, m_rotPolygon.x, m_rotPolygon.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_posPolygon.x, m_posPolygon.y, m_posPolygon.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxTrans);


	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldPolygon);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexturePolygon);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//================================================
//��������
//================================================
CWall* CWall::Create(void)
{
	CWall* pObject3D = new CWall;
	pObject3D->Init();

	return pObject3D;
}

//================================================
//���W�擾����
//================================================
D3DXVECTOR3 CWall::GetPos(void)
{
	return D3DXVECTOR3(m_posPolygon.x, m_posPolygon.y, m_posPolygon.z);
}

//================================================
//���擾����
//================================================
int CWall::GetWidth(void)
{
	return WALL_WIDTH;
}

//================================================
//�����擾����
//================================================
int CWall::GetHeight(void)
{
	return WALL_HEIGHT;
}

//================================================
//�����蔻�菈��
//================================================
float CWall::GetHeightMesh(float posx, float posz)
{
	float X = posx - m_posPolygon.x;
	float Z = posz - m_posPolygon.z;

	D3DXVECTOR3 vec1, vec2, nor;
	float fHeight;

	VERTEX_3D* pVtx = NULL;
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//X��Z���|���S���̓����ɂ���
	if ((X >= -WALL_WIDTH && X <= WALL_WIDTH) && (Z >= -WALL_HEIGHT && Z <= WALL_HEIGHT))
	{
		float s1 = ((pVtx[1].pos.x - pVtx[0].pos.x) * (Z - pVtx[0].pos.z) - (pVtx[1].pos.z - pVtx[0].pos.z) * (X - pVtx[0].pos.x));
		float s2 = ((pVtx[2].pos.x - pVtx[1].pos.x) * (Z - pVtx[1].pos.z) - (pVtx[2].pos.z - pVtx[1].pos.z) * (X - pVtx[1].pos.x));
		float s3 = ((pVtx[0].pos.x - pVtx[2].pos.x) * (Z - pVtx[2].pos.z) - (pVtx[0].pos.z - pVtx[2].pos.z) * (X - pVtx[2].pos.x));

		if ((s1 >= 0 && s2 >= 0 && s3 >= 0) || (s1 <= 0 && s2 <= 0 && s3 <= 0))
		{//����Ă���|���S����1���ڂȂ�
			vec1 = pVtx[1].pos - pVtx[0].pos;
			vec2 = pVtx[2].pos - pVtx[0].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);

			fHeight = pVtx[0].pos.y - (nor.x * (X - pVtx[0].pos.x) + nor.z * (Z - pVtx[0].pos.z)) / nor.y;
		}
		else
		{//����Ă���|���S����2���ڂȂ�
			vec1 = pVtx[3].pos - pVtx[1].pos;
			vec2 = pVtx[2].pos - pVtx[1].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);

			fHeight = pVtx[1].pos.y - (nor.x * (X - pVtx[1].pos.x) + nor.z * (Z - pVtx[1].pos.z)) / nor.y;
		}
		m_pVtxBuffPolygon->Unlock();
		return fHeight + m_posPolygon.y;
	}
	m_pVtxBuffPolygon->Unlock();
	return 0;
}