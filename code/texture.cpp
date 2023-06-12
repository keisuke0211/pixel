//========================================
// 
// �e�N�X�`���Ǘ�
// 
//========================================
// *** texture.cpp ***
//========================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "object\2D\bg2D.h"
#include "object\3D\floor.h"
#include "object\2D\block2D.h"
#include "object\3D\player.h"
#include "object\3D\enemy.h"
#include "object\3D\bullet.h"
#include "object\2D\effect2D.h"
#include "object\2D\text2D.h"

#include <assert.h>

// ��`
const char* CTexture::FILE_PATH = "data\\GAMEDATA\\TEXTURE\\TEXTURE_DATA.txt";

// �ÓI�����o�ϐ�
int CTexture::m_nTextureAll = 0;
char CTexture::s_FileName[CTexture::MAX_TEXTURE][TXT_MAX] = { NULL };

// �R���X�g���N�^
CTexture::CTexture()
{

}

// �f�X�g���N�^
CTexture::~CTexture()
{
}

//========================================
// �ǂݍ���
//========================================
HRESULT CTexture::Load(void)
{

	FILE *pFile;				// �t�@�C���|�C���^
	char aDataSearch[TXT_MAX];	// �f�[�^�����p


	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();


	// ��ޖ��̏��̃f�[�^�t�@�C�����J��
	pFile = fopen(FILE_PATH, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return S_OK;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "END"))
		{// �ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{// �܂�Ԃ�
			continue;
		}

		if (m_nTextureAll == MAX_TEXTURE)
		{// ��������������
			return S_OK;
		}

		if (!strcmp(aDataSearch, "BG"))		// �w�i
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);	// �t�@�C����

			// �e�N�X�`���ݒ�
			CBg::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "FLOOR")) // ��
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CFloor::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "BLOCK")) // �v���C���[
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CBlock2D::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "PLAYER")) // �v���C���[
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CPlayer::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "ENEMY"))		// �G�l�~�[
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CEnemy::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "BULLET"))	// �e
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CBullet::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "EFFECT")) // �G�t�F�N�g
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CEffect2D::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "TEXT")) // �e�L�X�g
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CText2D::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
	}

	return S_OK;
}

//========================================
// �S�Ẳ��
//========================================
void CTexture::Unload(void)
{
	CBg::Unload();			// �w�i
	CFloor::Unload();		// ��
	CBlock2D::Unload();		// �u���b�N
	CPlayer::Unload();		// �v���C���[
	CEnemy::Unload();		// �G�l�~�[
	CBullet::Unload();		// �o���b�g
	CEffect2D::Unload();	// �G�t�F�N�g
	CText2D::Unload();		// �e�L�X�g
}