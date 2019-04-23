#include "qtmprdemo.h"
#include <QtWidgets/QApplication>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingVolumeOpenGL);
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType)

//#define PI 3.1415926
//
//// The mouse motion callback, to turn "Slicing" on and off
//class vtkImageInteractionCallback : public vtkCommand
//{
//public:
//
//	static vtkImageInteractionCallback *New() {
//		return new vtkImageInteractionCallback;
//	};
//
//	vtkImageInteractionCallback() {
//		this->Slicing = 0;
//		this->ImageReslice = nullptr;
//		this->Interactor = nullptr;
//	};
//
//	void SetImageReslice(vtkImageReslice *reslice) {
//		this->ImageReslice = reslice;
//	};
//
//	vtkImageReslice *GetImageReslice() {
//		return this->ImageReslice;
//	};
//
//	void SetInteractor(vtkRenderWindowInteractor *interactor) {
//		this->Interactor = interactor;
//	};
//
//	vtkRenderWindowInteractor *GetInteractor() {
//		return this->Interactor;
//	};
//
//	void Execute(vtkObject *, unsigned long event, void *) override
//	{
//		vtkRenderWindowInteractor *interactor = this->GetInteractor();
//
//		int lastPos[2];
//		interactor->GetLastEventPosition(lastPos);
//		int currPos[2];
//		interactor->GetEventPosition(currPos);
//
//		if (event == vtkCommand::LeftButtonPressEvent)
//		{
//			vtkImageReslice *reslice = this->ImageReslice;
//			reslice->Update();
//			vtkMatrix4x4 *matrix = reslice->GetResliceAxes();
//			double center[3];
//			center[0] = matrix->GetElement(0, 3);
//			center[1] = matrix->GetElement(1, 3);
//			center[2] = matrix->GetElement(2, 3);
//
//			auto alpha = PI / 2;
//			auto beta = PI / 2;
//			auto gamma = PI / 2;
//
//			auto tmp = vtkSmartPointer<vtkMatrix4x4>::New();
//			auto res = vtkSmartPointer<vtkMatrix4x4>::New();
//
//			auto rotation_x_mat = vtkSmartPointer<vtkMatrix4x4>::New();
//			auto rotation_y_mat = vtkSmartPointer<vtkMatrix4x4>::New();
//			auto rotation_z_mat = vtkSmartPointer<vtkMatrix4x4>::New();
//			rotation_x_mat->Identity();
//			rotation_y_mat->Identity();
//			rotation_z_mat->Identity();
//			rotation_x_mat->SetElement(1, 1, cos(alpha));
//			rotation_x_mat->SetElement(2, 1, sin(alpha));
//			rotation_x_mat->SetElement(1, 2, -sin(alpha));
//			rotation_x_mat->SetElement(2, 2, cos(alpha));
//			rotation_y_mat->SetElement(0, 0, cos(beta));
//			rotation_y_mat->SetElement(2, 0, -sin(beta));
//			rotation_y_mat->SetElement(0, 2, sin(beta));
//			rotation_y_mat->SetElement(2, 2, cos(beta));
//			rotation_z_mat->SetElement(0, 0, cos(gamma));
//			rotation_z_mat->SetElement(1, 0, sin(gamma));
//			rotation_z_mat->SetElement(0, 1, -sin(gamma));
//			rotation_z_mat->SetElement(1, 1, cos(gamma));
//
//			//rotation_x_mat->Transpose();
//			//rotation_z_mat->Transpose();
//			//rotation_y_mat->Transpose();
//			res->DeepCopy(matrix);
//			vtkMatrix4x4::Multiply4x4(res, rotation_z_mat, res);
//			//vtkMatrix4x4::Multiply4x4(res, rotation_z_mat, res);
//			//vtkMatrix4x4::Multiply4x4(res, rotation_y_mat, res);
//			vtkMatrix4x4::Multiply4x4(res, rotation_y_mat, res);
//
//			//double array[] = { cos(theta),sin(theta),0,0,
//			//	-sin(theta),cos(theta),0,0,
//			//	0,0,1,0,
//			//	0,0,0,1 };
//
//			//auto a = PI / 2;
//			//auto b = PI / 2;
//			//auto g = 0;
//			//double result[] = {
//			//cos(b)*cos(g),-cos(a)*sin(g) + sin(a)*sin(b)*cos(g),sin(a)*sin(g) + cos(a)*sin(b)*cos(g),0,
//			//cos(b)*sin(g),cos(a)*cos(g) + sin(a)*sin(b)*sin(g),-sin(a)*cos(g) + cos(a)*sin(b)*sin(g),0,
//			//-sin(b),sin(a)*cos(b),cos(a)*cos(b),0,
//			//	0,0,0,1
//			//};
//
//			//matrix->SetElement(0, 0, cos(theta));
//			//matrix->SetElement(1, 0, -sin(theta));
//			//matrix->SetElement(0, 1, sin(theta));
//			//matrix->SetElement(1, 1, cos(theta));
//			matrix->DeepCopy(res);
//
//			matrix->SetElement(0, 3, center[0]);
//			matrix->SetElement(1, 3, center[1]);
//			matrix->SetElement(2, 3, center[2]);
//			matrix->Print(cout);
//			reslice->SetResliceAxes(matrix);
//			reslice->Update();
//			interactor->Render();
//			this->Slicing = 1;
//		}
//		//else if (event == vtkCommand::LeftButtonReleaseEvent)
//		//{
//		//	this->Slicing = 0;
//		//}
//		//else if (event == vtkCommand::MouseMoveEvent)
//		//{
//		//	if (this->Slicing)
//		//	{
//		//		vtkImageReslice *reslice = this->ImageReslice;
//		//		// Increment slice position by deltaY of mouse
//		//		int deltaY = lastPos[1] - currPos[1];
//		//		reslice->Update();
//		//		double sliceSpacing = reslice->GetOutput()->GetSpacing()[2];
//		//		vtkMatrix4x4 *matrix = reslice->GetResliceAxes();
//		//		// move the center point that we are slicing through
//		//		//double point[4];
//		//		//double center[4];
//		//		//point[0] = 0.0;
//		//		//point[1] = 0.0;
//		//		//point[2] = sliceSpacing * deltaY;
//		//		//point[3] = 1.0;
//		//		//matrix->MultiplyPoint(point, center);
//		//		//matrix->SetElement(0, 3, center[0]);
//		//		//matrix->SetElement(1, 3, center[1]);
//		//		//matrix->SetElement(2, 3, center[2]);
//		//		interactor->Render();
//		//	}
//		//	else
//		//	{
//		//		vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(
//		//			interactor->GetInteractorStyle());
//		//		if (style)
//		//		{
//		//			style->OnMouseMove();
//		//		}
//		//	}
//		//}
//	};
//
//private:
//
//	// Actions (slicing only, for now)
//	int Slicing;
//	double theta{ 0 };
//	// Pointer to vtkImageReslice
//	vtkImageReslice *ImageReslice;
//
//	// Pointer to the interactor
//	vtkRenderWindowInteractor *Interactor;
//};
//
//
//// The program entry point
//int main(int argc, char *argv[])
//{
//	// Start by loading some data.
//	auto reader = vtkSmartPointer<vtkDICOMImageReader>::New();
//	reader->SetDirectoryName("E:\\CarotidAnalyze\\VirtualEndoscopy\\data\\Head");
//	reader->Update();
//	int extent[6];
//	double spacing[3];
//	double origin[3];
//
//
//	reader->GetOutputInformation(0)->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
//	reader->GetOutput()->GetSpacing(spacing);
//	reader->GetOutput()->GetOrigin(origin);
//
//	double center[3];
//	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
//	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
//	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);
//
//	// Matrices for axial, coronal, sagittal, oblique view orientations
//	static double axialElements[16] = {
//		1, 0, 0, 0,
//		0, 1, 0, 0,
//		0, 0, 1, 0,
//		0, 0, 0, 1 };
//
//	static double coronalElements[16] = {
//		1, 0, 0, 0,
//		0, 0, 1, 0,
//		0,-1, 0, 0,
//		0, 0, 0, 1 };
//
//	static double sagittalElements[16] = {
//		0, 0,1, 0,
//		-1, 0, 0, 0,
//		0,-1, 0, 0,
//		0, 0, 0, 1 };
//
//	// Set the slice orientation
//	vtkSmartPointer<vtkMatrix4x4> resliceAxes =
//		vtkSmartPointer<vtkMatrix4x4>::New();
//	resliceAxes->DeepCopy(sagittalElements);
//	// Set the point through which to slice
//	resliceAxes->SetElement(0, 3, center[0]);
//	resliceAxes->SetElement(1, 3, center[1]);
//	resliceAxes->SetElement(2, 3, center[2]);
//
//	// Extract a slice in the desired orientation
//	vtkSmartPointer<vtkImageReslice> reslice =
//		vtkSmartPointer<vtkImageReslice>::New();
//	reslice->SetInputConnection(reader->GetOutputPort());
//	reslice->SetOutputDimensionality(2);
//	reslice->SetResliceAxes(resliceAxes);
//	reslice->SetInterpolationModeToLinear();
//
//	// Create a greyscale lookup table
//	vtkSmartPointer<vtkLookupTable> table =
//		vtkSmartPointer<vtkLookupTable>::New();
//	table->SetRange(-300, 700); // image intensity range
//	table->SetValueRange(0.0, 1.0); // from black to white
//	table->SetSaturationRange(0.0, 0.0); // no color saturation
//	table->SetRampToLinear();
//	table->Build();
//
//	// Map the image through the lookup table
//	vtkSmartPointer<vtkImageMapToColors> color =
//		vtkSmartPointer<vtkImageMapToColors>::New();
//	color->SetLookupTable(table);
//	color->SetInputConnection(reslice->GetOutputPort());
//
//	// Display the image
//	vtkSmartPointer<vtkImageActor> actor =
//		vtkSmartPointer<vtkImageActor>::New();
//	actor->GetMapper()->SetInputConnection(color->GetOutputPort());
//
//	vtkSmartPointer<vtkRenderer> renderer =
//		vtkSmartPointer<vtkRenderer>::New();
//	renderer->AddActor(actor);
//
//	vtkSmartPointer<vtkRenderWindow> window =
//		vtkSmartPointer<vtkRenderWindow>::New();
//	window->AddRenderer(renderer);
//
//	// Set up the interaction
//	vtkSmartPointer<vtkInteractorStyleImage> imageStyle =
//		vtkSmartPointer<vtkInteractorStyleImage>::New();
//	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
//		vtkSmartPointer<vtkRenderWindowInteractor>::New();
//	interactor->SetInteractorStyle(imageStyle);
//	window->SetInteractor(interactor);
//	window->Render();
//
//	vtkSmartPointer<vtkImageInteractionCallback> callback =
//		vtkSmartPointer<vtkImageInteractionCallback>::New();
//	callback->SetImageReslice(reslice);
//	callback->SetInteractor(interactor);
//
//	imageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);
//	imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
//	imageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);
//
//	// Start interaction
//	// The Start() method doesn't return until the window is closed by the user
//	interactor->Start();
//
//	return EXIT_SUCCESS;
//}





int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtMprDemo w;
	w.show();
	return a.exec();
}
