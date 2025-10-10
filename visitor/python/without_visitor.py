class Circle:
    def __init__(self, radius):
        self.radius = radius

    def calculate_area(self):
        print(f"\nCircle")
        return 3.14 * self.radius * self.radius

    def draw(self):
        print(f"Drawing a circle with radius {self.radius}\n")


class Square:
    def __init__(self, side):
        self.side = side

    def calculate_area(self):
        print(f"\nSquare")
        return self.side * self.side

    def draw(self):
        print(f"Drawing a square with side {self.side}\n")


shapes = [Circle(5), Square(4)]


print(f"Area: {shapes[0].calculate_area()}")
shapes[0].draw()
print(f"Area: {shapes[1].calculate_area()}")
shapes[1].draw()
