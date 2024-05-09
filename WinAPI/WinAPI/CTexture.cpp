#include "pch.h"
#include "CTexture.h"

#include "CEngine.h"

CTexture::CTexture()
	: m_hBitmap(nullptr)
	, m_hDC(nullptr)
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBitmap);
}

int CTexture::Load(const wstring& _FilePath)
{
	// 지정된 경로로부터 비트맵 이미지를 메모리에 로딩하고 핸들값을 받아둠
	m_hBitmap = (HBITMAP)LoadImage(nullptr, _FilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		
	// 로딩이 정상적으로 되었는지 비트맵 핸들값을 확인
	if (nullptr == m_hBitmap)
	{
		DWORD err = GetLastError();
		wchar_t buffer[256] = {};
		swprintf_s(buffer, 256, L"텍스쳐 로딩 실패\n에러 번호 : %d", err);
		MessageBox(nullptr, buffer, L"에러 발생", MB_OK);

		return E_FAIL;
	}
		
	// 비트맵을 선택해서 연결해줄 DC 를 생성
	m_hDC = CreateCompatibleDC(CEngine::Get()->GetMainDC());

	// 비트맵과 생성한 DC 를 연결
	DeleteObject(SelectObject(m_hDC, m_hBitmap));
	
	// 메모리에 로딩한 비트맵의 정보를 받아온다.
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BitInfo);

	return S_OK;
}