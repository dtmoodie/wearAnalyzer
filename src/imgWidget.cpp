#include "imgWidget.h"
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkImageViewer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <QVTKWidget.h>
#include <vtkQuad.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <opencv2/highgui.hpp>

imgWidget::imgWidget(QWidget* parent):
QVTKWidget(parent)
{
	_renderer = vtkRenderer::New();
	_renderer->SetBackground(0, 0, 0);
	_renderer->ResetCamera();
	GetRenderWindow()->AddRenderer(_renderer);

	// Setup the quad for image display
	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint(0.0, 0.0, 0.0);
	points->InsertNextPoint(1.0, 0.0, 0.0);
	points->InsertNextPoint(1.0, 1.0, 0.0);
	points->InsertNextPoint(0.0, 2.0, 0.0);

	vtkSmartPointer<vtkCellArray> polygons = vtkSmartPointer<vtkCellArray>::New();
	vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();
	polygon->GetPointIds()->SetNumberOfIds(4); //make a quad
	polygon->GetPointIds()->SetId(0, 0);
	polygon->GetPointIds()->SetId(1, 1);
	polygon->GetPointIds()->SetId(2, 2);
	polygon->GetPointIds()->SetId(3, 3);

	polygons->InsertNextCell(polygon);

	vtkSmartPointer<vtkFloatArray> textureCoordinates =
		vtkSmartPointer<vtkFloatArray>::New();
	textureCoordinates->SetNumberOfComponents(3);
	textureCoordinates->SetName("TextureCoordinates");

	float tuple[3] = { 0.0, 0.0, 0.0 };
	textureCoordinates->InsertNextTuple(tuple);
	tuple[0] = 1.0; tuple[1] = 0.0; tuple[2] = 0.0;
	textureCoordinates->InsertNextTuple(tuple);
	tuple[0] = 1.0; tuple[1] = 1.0; tuple[2] = 0.0;
	textureCoordinates->InsertNextTuple(tuple);
	tuple[0] = 0.0; tuple[1] = 2.0; tuple[2] = 0.0;
	textureCoordinates->InsertNextTuple(tuple);

	_quad = vtkSmartPointer<vtkPolyData>::New();
	_quad->SetPoints(points);
	_quad->SetPolys(polygons);
	_quad->GetPointData()->SetTCoords(textureCoordinates);

	_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	_mapper->SetInputData(_quad);
	_texture = vtkSmartPointer<cvTexture>::New();
	//_texture->setImage(cv::imread("D:/sexy/DSCF7514.JPG"));

	_texturedQuad = vtkSmartPointer<vtkActor>::New();
	_texturedQuad->SetMapper(_mapper);
	_texturedQuad->SetTexture(_texture);
	_renderer->AddActor(_texturedQuad);
	show();
}
void
imgWidget::setImage(cv::InputArray img)
{
	_texture->setImage(img);
	_texture->Load(_renderer);
}

