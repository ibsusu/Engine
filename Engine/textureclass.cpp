////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"


TextureClass::TextureClass()
{
	m_texture = 0;
	int m_red = 220;
	int m_green = 220;
	int m_blue = 220;
	int m_alpha = 255;
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}


bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if(FAILED(result))
	{
		return false;
	}
	//float *texArray = (float *)malloc(4*256*256*sizeof(float));
	m_red = rand() % 256;
	m_green = rand() % 256;
	m_blue = rand() % 256;
	m_alpha = rand() % 256;

	unsigned char *texArray = (unsigned char *)malloc(4 * 256 * 256 * sizeof(unsigned char));
	for(int i=0;i<256*256*4;i++){
		if(i%4 ==  0){
			texArray[i] = (unsigned char)m_red;
		}
		if(i%4 ==  1){
			texArray[i] = (unsigned char)m_green;
		}
		if(i%4 ==  2){
			texArray[i] = (unsigned char)m_blue;
		}
		if(i%4 ==  3){
			texArray[i] = (unsigned char)m_alpha;
		}
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC *thing;
	
	
	D3D11_TEXTURE2D_DESC td_thing;
	ZeroMemory(&td_thing, sizeof(D3D11_TEXTURE2D_DESC));
	td_thing.ArraySize = 1;
	td_thing.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td_thing.CPUAccessFlags = 0;
	td_thing.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td_thing.Height = 256;
	td_thing.Width = 256;
	td_thing.MipLevels = 1;
	td_thing.MiscFlags = 0;
	td_thing.SampleDesc.Count = 1;
	td_thing.SampleDesc.Quality = 0;
	td_thing.Usage = D3D11_USAGE_DEFAULT;
	
	D3D11_SUBRESOURCE_DATA boxTexInitData;
    ZeroMemory(&boxTexInitData, sizeof(D3D11_SUBRESOURCE_DATA));
    boxTexInitData.pSysMem = texArray;
	boxTexInitData.SysMemPitch = static_cast<UINT>(256*4);
	boxTexInitData.SysMemSlicePitch = static_cast<UINT>( 4*256*256*sizeof(unsigned char));

	ID3D11Texture2D *tex = NULL;
	result = device->CreateTexture2D(&td_thing,&boxTexInitData,&tex);

	if(FAILED(result)){
			MessageBox(NULL, L"Could not initialize the Texture.", L"Error", MB_OK);
		return false;}
	
	result = device->CreateShaderResourceView(tex,NULL,&m_texture);
	if(FAILED(result)){return false;}
	/**/

	return true;
}


void TextureClass::Shutdown()
{
	// Release the texture resource.
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}


ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}