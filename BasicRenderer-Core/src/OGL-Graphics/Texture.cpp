#include "Texture.h"


Texture::Texture(const std::string& path) :m_RendererID(0), m_FilePath(texturePath + path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0) {

	m_LocalBuffer = loadTexture(m_FilePath.c_str(), m_Width, m_Height);
	if (!m_LocalBuffer)
	{
		std::cout << "Error cargando el fichero: "
			<< path << std::endl;
		exit(-1);
	}

	GLcall(glGenTextures(1, &m_RendererID));
	GLcall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	GLcall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, (GLvoid*)m_LocalBuffer));

	GLcall(glGenerateMipmap(GL_TEXTURE_2D));

	GLcall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR));
	GLcall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLcall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLcall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));

	//Filtro anisotropico
	/*if (glewIsExtensionSupported("GL_EXT_texture_filter_anisotropic")) {
		std::cout << "Filtro anisotropico soportado"<< std::endl;
	}*/

	GLfloat fLargest;
	GLcall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest));
	GLcall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest));

	GLcall(glBindTexture(GL_TEXTURE_2D, 0));


	delete[] m_LocalBuffer;

}

Texture::~Texture() {
	GLcall(glDeleteTextures(1, &m_RendererID));
}

void Texture::bind(unsigned int slot) const {
	GLcall(glActiveTexture(GL_TEXTURE0 + slot));
	GLcall(glBindTexture(GL_TEXTURE_2D, m_RendererID));


}
void Texture::unbind() const {
	GLcall(glBindTexture(GL_TEXTURE_2D, 0));
}



unsigned char* Texture::loadTexture(const char* fileName, unsigned int& w, unsigned int& h)
{
	FreeImage_Initialise(TRUE);

	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fileName, 0);
	if (format == FIF_UNKNOWN)
		format = FreeImage_GetFIFFromFilename(fileName);
	if ((format == FIF_UNKNOWN) || !FreeImage_FIFSupportsReading(format))
		return NULL;

	FIBITMAP* img = FreeImage_Load(format, fileName);
	if (img == NULL)
		return NULL;

	FIBITMAP* tempImg = img;
	img = FreeImage_ConvertTo32Bits(img);
	FreeImage_Unload(tempImg);

	w = FreeImage_GetWidth(img);
	h = FreeImage_GetHeight(img);

	//BGRA a RGBA
	unsigned char* map = new unsigned char[4 * w * h];
	char* buff = (char*)FreeImage_GetBits(img);

	for (unsigned int j = 0; j < w * h; j++) {
		map[j * 4 + 0] = buff[j * 4 + 2];
		map[j * 4 + 1] = buff[j * 4 + 1];
		map[j * 4 + 2] = buff[j * 4 + 0];
		map[j * 4 + 3] = buff[j * 4 + 3];
	}

	FreeImage_Unload(img);
	FreeImage_DeInitialise();

	return map;
}