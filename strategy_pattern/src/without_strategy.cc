
// #include <iostream>
// #include <string>

// class SimpleShoppingCart {
// public:
//   enum PaymentMethodType { CREDIT_CARD, PAYPAL };

//   void checkout(int amount, PaymentMethodType method_type,
//                 const std::string &account_info) {
//     std::cout << "Processing checkout (without Strategy Pattern)..."
//               << std::endl;

//     if (method_type == CREDIT_CARD) {
//       // Logic for Credit Card is embedded here
//       std::cout << "Paying " << amount << " using Credit Card: " << account_info
//                 << std::endl;
//       // Additional credit card validation logic goes here...
//     } else if (method_type == PAYPAL) {
//       // Logic for PayPal is embedded here
//       std::cout << "Paying " << amount << " using PayPal: " << account_info
//                 << std::endl;
//       // Additional PayPal API calls/logic goes here...
//     } else {
//       std::cout << "Error: Unknown payment method selected." << std::endl;
//     }
//   }
// };

// // int main() {
// //   SimpleShoppingCart cart;
// //   int purchase_amount = 100;

// //   // Client must pass in a type identifier and general info
// //   cart.checkout(purchase_amount, SimpleShoppingCart::CREDIT_CARD,
// //                 "1234-5678-9012-3456");

// //   std::cout << std::endl;

// //   cart.checkout(purchase_amount, SimpleShoppingCart::PAYPAL,
// //                 "user@example.com");

// //   return 0;
// // }
