#pragma once



typedef enum
{
	SHAPE_CIRCLE,
	SHAPE_SQUARE,
	SHAPE_TRIANGLE,
	SHAPE_RECTANGLE,
} ShapeType;

typedef struct
{
	double c_x, c_y;
	double r;
} CirlceParameters;

typedef struct
{
	double x0, y0;
	double a;
} SquareParameters;

typedef struct
{
	double x0, y0;
	double x1, y1;  
} RectangleParameters;

typedef struct
{
	double x2, y2;
	double x3, y3;
	double x1, y1;

} TriangleParameters;

typedef struct
{
	ShapeType type;
	union
	{
		CirlceParameters circle;
		SquareParameters square;
		RectangleParameters rectangle;
		TriangleParameters triangle;
	} p;
	double xmin, xmax, ymin, ymax;
} Shape;