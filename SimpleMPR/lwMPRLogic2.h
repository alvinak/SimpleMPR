#ifndef _LW_MPR_LOGIC2_H
#define _LW_MPR_LOGIC2_H

#include <vector>
#include <memory>
#include <iostream>
#include <list>

#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>

using namespace std;

// ������һ������
static void normalize(vector<double>& v);

// ������˲���
static vector<double> crossProduct(vector<double>& a, vector<double>& b);

// ����ʵ��MPR�߼�
class lwMPRLogic2
{
public:
	lwMPRLogic2();
	~lwMPRLogic2();

	enum MPR_TYPE
	{
		AXIAL,
		CORONAL,
		SAGITTAL,
		OBLIQUE
	};

	// ������ʾ����
	// TODO:��ֹ�������޸�
	void SetView(MPR_TYPE type);
	MPR_TYPE GetView();

	// ��ǰ�ز����ķ�������
	//  x1 x2 x3 0
	//  y1 y2 y3 0
	//  z1 z2 z3 cz
	//  0  0  0  1
	// ����ͼ���ʼ������ͼ������
	//		1.x�᷽��Ϊ(x1,y1,z1)
	//		2.y�᷽��Ϊ(x2,y2,z2)
	//		3.z�᷽��Ϊ(x3,y3,z3)
	//		4.��ת����Ϊ(0,0,cz)
	vector<double>	GetXAxis();
	vector<double>	GetYAxis();
	vector<double>	GetZAxis();

	// ͬ����ͼ��vx/vy�ı�ʱ
	// �ص������������ı䵱ǰ��ͼ
	void			OnXAxisUpdated(vector<double>& v);
	void			OnYAxisUpdated(vector<double>& v);
	void			OnZAxisUpdated(vector<double>& v);

	// ��������/��ȡʮ�ֹ��λ��
	double			GetXPosition();
	double			GetYPosition();
	void			SetXPosition(double v);
	void			SetYPosition(double v);
	
	// ���ڸı䵱ǰ��Ƭ
	double			GetZPosition();
	void			SetZPosition(double v);

	// ���ڸı䵱ǰ��Ƭ
	void			UpdateVX(vector<double>& v);
	void			UpdateVY(vector<double>& v);
	vector<double>	GetVX();
	vector<double>	GetVY();

private:
	// ��ǰʮ�ֽ����λ��
	double	xpos{ 0 };
	double	ypos{ 0 };

	// ��ǰʮ�ֽ�������
	vector<double> vx{ 1,0,0 };
	vector<double> vy{ 0,1,0 };

	vtkSmartPointer<vtkMatrix4x4>			axis_matrix;
	MPR_TYPE								view_type{ AXIAL };
	const double AXIAL_VIEW[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	const double CORONAL_VIEW[16] = {
		1, 0, 0, 0,
		0, 0, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 1 };
	const double SAGITTAL_VIEW[16] = {
		0, 0, 1, 0,
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 1 };
};

#endif // !_LW_MPR_LOGIC2_H
