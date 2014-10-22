#ifndef IMGWIDGET_H
#define IMGWIDGET_H

#include <qwidget.h>
#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
#include <opencv2/core.hpp>
#include <opencv2/core/opengl.hpp>


#include <vtkRenderWindow.h>
#include <vtkOpenGLRenderWindow.h>
#include <vtkScalarsToColors.h>
#include <vtkRenderer.h>
#include <vtkgl.h>
#include <vtkOpenGLTexture.h>
#include <vtkOpenGL.h>
#include <vtkOpenGLError.h>
#include <vtkTextureObject.h>

class vtkActor;
class vtkPolyData;
class vtkPolyDataMapper;
class imgWidget : public QVTKWidget
{

	class cvTextureObject : public vtkTextureObject
	{

	};
	
	class cvTexture : public vtkOpenGLTexture
	{
	public:
		static cvTexture* New()
		{
			return new cvTexture();
		}
		vtkTypeMacro(cvTexture, vtkOpenGLTexture);
		cvTexture():
			vtkOpenGLTexture()
		{
			this->RenderWindow = 0;
			this->IsDepthTexture = 0;
			this->TextureType = GL_TEXTURE_2D;

			this->TextureObject = 0;
		}
		bool setImage(cv::InputArray img)
		{
			texture.copyFrom(img);
			Index = texture.texId();
			glDeleteLists(static_cast<GLuint>(Index), static_cast<GLsizei>(0));
			vtkOpenGLCheckErrorMacro("failed at glDeleteLists");
			glNewList(static_cast<GLuint>(Index), GL_COMPILE);
			vtkOpenGLCheckErrorMacro("failed at glNewList");
			return true;
		}
		void Load(vtkRenderer* ren)
		{
			vtkOpenGLRenderWindow* renWin =	static_cast<vtkOpenGLRenderWindow*>(ren->GetRenderWindow());
			if (this->GetMTime() > this->LoadTime.GetMTime() ||
				(this->GetLookupTable() && this->GetLookupTable()->GetMTime() >
				this->LoadTime.GetMTime()) ||
				renWin != this->RenderWindow.GetPointer() ||
				renWin->GetContextCreationTime() > this->LoadTime)
			{
				this->RenderWindow = renWin;
				if (this->TextureObject == 0)
				{
					this->TextureObject = vtkTextureObject::New();
				}
				this->TextureObject->SetContext(renWin);
				GLint maxDimGL;
				glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxDimGL);
				vtkOpenGLCheckErrorMacro("failed at glGetIntegerv");
				

			}
		}
		void Initialize(vtkRenderer* vtkNotUsed(ren))
		{

		}

	private:
		cv::ogl::Texture2D texture;
	};
	Q_OBJECT
public:
	imgWidget(QWidget* parent);
	void setImage(cv::InputArray img);

private:
	vtkSmartPointer<vtkRenderer>		_renderer;
	vtkSmartPointer<vtkRenderWindow>	_window;
	vtkSmartPointer<vtkPolyData>		_quad;
	vtkSmartPointer<vtkActor>			_texturedQuad;
	vtkSmartPointer<cvTexture>			_texture;
	vtkSmartPointer<vtkPolyDataMapper>  _mapper;
};




#endif