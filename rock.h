//==================================================================
//
//�Ώ��� [rock.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _ROCK_H_					//���̃}�N����`������ĂȂ�������
#define _ROCK_H_					//2�d�C���N���[�h�h�~�̃}�N����`

//================================================
//�C���N���[�h
//================================================
#include "objectX.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X
//================================================
class CRock :public CObjectX
{
public:
    CRock();
    ~CRock();

    //static CPlayer* Create(
    //    DRAW_TYPE drawtype,
    //    int width,
    //    int height,
    //    float scrollX,
    //    float scrollY,
    //    int animeFrameU,
    //    int animeFrameV,
    //    int animePattern,
    //    float posX,
    //    float posY,
    //    float posZ,
    //    float rotZ
    //);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    //static CRock* Create();
    static CRock* Create(float X,float Y,float Z);


    static HRESULT Load(void);
    static void Unload(void);
    float GetHeight(float posx, float posz);


private:
    static LPD3DXMESH m_pMesh;
    static LPD3DXBUFFER m_pBuffMat;
    static DWORD m_dwNumMat;

    static D3DXVECTOR3 m_vtxMin;
    static D3DXVECTOR3 m_vtxMax;
    static D3DXVECTOR3 m_size;
};

#endif