class Visitor:
    def visit_circle(self, circle):
        raise NotImplementedError

    def visit_square(self, square):
        raise NotImplementedError


class Shape:
    def accept(self, visitor):
        raise NotImplementedError


class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius

    def accept(self, visitor: Visitor):
        visitor.visit_circle(self)


class Square(Shape):
    def __init__(self, side):
        self.side = side

    def accept(self, visitor):
        visitor.visit_square(self)


class Drawer(Visitor):
    def visit_circle(self, circle):
        print(f"Drawing a circle with radius {circle.radius}")

    def visit_square(self, square):
        print(f"Drawing a square with side {square.side}")


class AreaCalculator(Visitor):
    def visit_circle(self, circle):
        print(f"Area of circle: {3.14 * circle.radius * circle.radius}")

    def visit_square(self, square):
        print(f"Area of square: {square.side * square.side}")


# Client code
shapes = [Circle(5), Square(4)]

area_calculator = AreaCalculator()
drawer = Drawer()

shapes[0].accept(area_calculator)
shapes[0].accept(drawer)
shapes[1].accept(area_calculator)
shapes[1].accept(drawer)
