
#pragma once

#ifdef _DEBUG
#define printf_s( ... );	printf_s( ##__VA_ARGS__ );
#else
#define printf_s( ... );	
#endif // DEBUG


template <typename T>
inline void SafeDelete( T* &p )
{
	if ( p != nullptr )
	{
		delete p;
		p = nullptr;
	}
}

template <typename T>
inline void SafeArrayDelete( T* &p )
{
	if ( p != nullptr )
	{
		delete[] p;
		p = nullptr;
	}
}

template <typename T>
inline void SafeRelease( T* &p )
{
	if ( p != nullptr )
	{
		p->Release();
		p = nullptr;
	}
}

#define NN_PI 3.14159265358979

// 1 Radian = 180/PI Degree
// 1 Degree = PI/180 Radian
inline float NNDegreeToRadian( float n )
{
	return n / 180.f * (float)NN_PI;
}
inline double NNDegreeToRadian( double n )
{
	return n / 180 * NN_PI;
}

inline float NNRadianToDegree( float n )
{
	return n * 180.f / (float)NN_PI;
}
inline double NNRadianToDegree( double n )
{
	return n * 180 / NN_PI;
}


//�־��� ������ ���� X�� ���̸� �ڻ������� ����س�
inline float NNDegreeToX( float angle )
{
	return (float)cos(NN_PI*angle/180);
}

//�־��� ������ ���� Y�� ���̸� �������� ����س�
inline float NNDegreeToY( float angle )
{
	return (float)sin(NN_PI*angle/180);
}

// #define NNCREATE_FUNC(CLASS_NAME) \
// 	static CLASS_NAME* Create() \
// 	{ \
// 		CLASS_NAME* pInstance = new CLASS_NAME(); \
// 		return pInstance; \
// 	}

#define SINGLETON(type) \
	public: \
	static type* GetInstance() {static type s; return &s;}
