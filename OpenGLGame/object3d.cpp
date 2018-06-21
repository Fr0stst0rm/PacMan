#include "object3d.h"

Object3D::Object3D() : x(0), y(0), z(0)
{
}

Object3D::~Object3D()
{
}

void Object3D::setTexture(std::string path)
{
	GLsizei w, h;
	tgaInfo *info = 0;
	int mode;

	info = tgaLoad((char *)path.c_str());

	if (info->status != TGA_OK) {
		fprintf(stderr, "error loading texture image: %d\n", info->status); // Wall texture

		return;
	}
	if (info->width != info->height) {
		fprintf(stderr, "Image size %d x %d is not rectangular, giving up.\n",
			info->width, info->height);
		return;
	}

	mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
	glGenTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Upload the texture bitmap. 
	w = info->width;
	h = info->height;

	GLint format = (mode == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
		GL_UNSIGNED_BYTE, info->imageData);

	tgaDestroy(info);
}

void Object3D::setPos(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Object3D::draw()
{

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texture);

	glPushMatrix();
	glTranslatef(x, y, z);
	//glTranslatef(0, y, 0);
	//glTranslatef(0, 0, z);

	

	glScalef(size, size, 1.0f);

	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);
		
	createMesh();	
	
	glPopMatrix();
	
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

GLuint Object3D::getTexture()
{
	return texture;
}

void Object3D::setScale(float size)
{
	this->size = size;
}

void Object3D::setZRotation(float deg)
{
	this->rotationZ = deg;
}
