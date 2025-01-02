class Animal {
    void makeSound() {
        System.out.println("Animal sound");
    }
}

class Dog extends Animal {
    @Override
    void makeSound() {
        System.out.println("Bark");
    }
}

class Cat extends Animal {
    @Override
    void makeSound() {
        System.out.println("Meow");
    }
}

public class PolymorphismExample {
    public static void main(String[] args) {
        Animal doggy = new Dog();
        Animal kitty = new Cat();
        doggy.makeSound();
        kitty.makeSound();
    }
}