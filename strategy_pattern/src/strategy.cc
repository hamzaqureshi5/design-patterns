
#include <iostream>
#include <memory>
#include <string>

class PaymentStrategy {
public:
  virtual ~PaymentStrategy() = default;
  virtual void pay(int amount) const = 0;
};

class CreditCardPayment : public PaymentStrategy {
private:
  std::string card_number;

public:
  CreditCardPayment(const std::string &number) : card_number(number) {}
  void pay(int amount) const override {
    // This method encapsulates all Credit Card specific logic
    std::cout << "Paying " << amount << " using Credit Card: " << card_number
              << std::endl;
    // ... (API calls, validation logic specific to CC)
  }
};

class PayPalPayment : public PaymentStrategy {
private:
  std::string email;

public:
  PayPalPayment(const std::string &email) : email(email) {}
  void pay(int amount) const override {
    // This method encapsulates all PayPal specific logic
    std::cout << "Paying " << amount << " using PayPal: " << email << std::endl;
    // ... (API calls, validation logic specific to PayPal)
  }
};

class ShoppingCart {
private:
  // Uses a smart pointer to own the current strategy object.
  std::unique_ptr<PaymentStrategy> payment_strategy_;

public:
  // Method to change the strategy dynamically at runtime.
  void set_payment_strategy(std::unique_ptr<PaymentStrategy> strategy) {
    payment_strategy_ = std::move(strategy);
  }

  void checkout(int amount) const {
    if (payment_strategy_) {
      std::cout << "Processing checkout (with Strategy Pattern)..."
                << std::endl;
      // Delegation: the context delegates the work to the current strategy
      // object
      payment_strategy_->pay(amount);
    } else {
      std::cout << "Cannot checkout: No payment strategy set." << std::endl;
    }
  }
};

int main() {
  ShoppingCart cart;
  int purchase_amount = 100;
  std::unique_ptr<PaymentStrategy> credit_card =
      std::make_unique<CreditCardPayment>("1234-5678-9012-3456");
  cart.set_payment_strategy(std::move(credit_card));
  cart.checkout(purchase_amount);

  return 0;
}
