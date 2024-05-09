#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
	Release_Map(m_mapTex);
}

void CAssetMgr::Init()
{
}

CTexture* CAssetMgr::LoadTexture(const wstring& _strKey, const wstring& _RelativePath)
{
	// ������ Ű������ �̹� �ؽ��İ� �ִ��� Ȯ��
	CTexture* pTexture = FindTexture(_strKey);

	// �̹� ������ �װ� ��ȯ
	if (pTexture)
		return pTexture;

	// ��������, �Է����� ���� ����ο� Content ���������� ��θ� ���ļ� ������ ���� ��θ� ����
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _RelativePath;

	// �ؽ��� ��ü�ϳ� ����, �ϼ��� ��η� ��Ʈ�� �ε� ����
	pTexture = new CTexture;
	if (FAILED(pTexture->Load(strFilePath)))
	{
		delete pTexture;
		return nullptr;
	}
	

	// �ε��� �ؽ��ĸ� AssetMgr �� ���
	m_mapTex.insert(make_pair(_strKey, pTexture));

	// �ε��� �ؽ��ĸ� ��ȯ
	return pTexture;
}

CTexture* CAssetMgr::FindTexture(const wstring& _strKey)
{
	// ������ Ű������ �ؽ��İ� �ִ��� Ȯ��
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	// �ؽ��İ� �̹� �־����� �װ� ��ȯ
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return iter->second;
}
