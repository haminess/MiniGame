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
	// ������ ��ηκ��� ��Ʈ�� �̹����� �޸𸮿� �ε��ϰ� �ڵ鰪�� �޾Ƶ�
	m_hBitmap = (HBITMAP)LoadImage(nullptr, _FilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		
	// �ε��� ���������� �Ǿ����� ��Ʈ�� �ڵ鰪�� Ȯ��
	if (nullptr == m_hBitmap)
	{
		DWORD err = GetLastError();
		wchar_t buffer[256] = {};
		swprintf_s(buffer, 256, L"�ؽ��� �ε� ����\n���� ��ȣ : %d", err);
		MessageBox(nullptr, buffer, L"���� �߻�", MB_OK);

		return E_FAIL;
	}
		
	// ��Ʈ���� �����ؼ� �������� DC �� ����
	m_hDC = CreateCompatibleDC(CEngine::Get()->GetMainDC());

	// ��Ʈ�ʰ� ������ DC �� ����
	DeleteObject(SelectObject(m_hDC, m_hBitmap));
	
	// �޸𸮿� �ε��� ��Ʈ���� ������ �޾ƿ´�.
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BitInfo);

	return S_OK;
}