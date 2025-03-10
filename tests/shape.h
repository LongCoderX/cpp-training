

enum class shape_type { circle, triangle };

class shape {
public:
  virtual ~shape();
};

class circle : public shape {
public:
  circle(double r);
  ~circle() override;
  double radius_;
};
class triangle : public shape {
public:
  triangle(double a, double b, double c);
  ~triangle() override;
  double a_, b_, c_;
};

shape *create_shape(shape_type type);