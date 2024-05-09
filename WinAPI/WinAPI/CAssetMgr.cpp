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
	// 동일한 키값으로 이미 텍스쳐가 있는지 확인
	CTexture* pTexture = FindTexture(_strKey);

	// 이미 있으면 그걸 반환
	if (pTexture)
		return pTexture;

	// 없었으면, 입력으로 들어온 상대경로와 Content 폴더까지의 경로를 합쳐서 파일의 최종 경로를 만들어냄
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _RelativePath;

	// 텍스쳐 객체하나 생성, 완성된 경로로 비트맵 로딩 진행
	pTexture = new CTexture;
	if (FAILED(pTexture->Load(strFilePath)))
	{
		delete pTexture;
		return nullptr;
	}
	

	// 로딩된 텍스쳐를 AssetMgr 에 등록
	m_mapTex.insert(make_pair(_strKey, pTexture));

	// 로딩한 텍스쳐를 반환
	return pTexture;
}

CTexture* CAssetMgr::FindTexture(const wstring& _strKey)
{
	// 동일한 키값으로 텍스쳐가 있는지 확인
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	// 텍스쳐가 이미 있었으면 그걸 반환
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return iter->second;
}
