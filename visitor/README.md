# 🧭 Visitor Design Pattern (C++17)

This project demonstrates the **Visitor Design Pattern** implemented in modern **C++17**.  
It uses an **expression tree** (similar to a mini Abstract Syntax Tree used in compilers) to show how the Visitor pattern enables adding new operations — such as **evaluation** and **pretty-printing** — without modifying existing element classes.

---

## 📘 Overview

The **Visitor Pattern** is a **behavioral design pattern** that lets you add new operations to a class hierarchy **without altering** the classes themselves.

It achieves this by separating:
- The **data structure** (e.g., expressions or AST nodes)
- From the **operations** performed on it (e.g., evaluation, printing, optimization)

---

## ⚙️ Components

| Component | Description |
|------------|-------------|
| **Visitor Interface** | Declares `visit()` methods for each concrete element type. |
| **Concrete Visitors** | Implement specific operations (e.g., evaluate or print). |
| **Element Interface** | Declares `accept()` to accept a visitor. |
| **Concrete Elements** | Real objects (like `AddExpr`, `MulExpr`, `NumberExpr`) that call `visitor.visit(this)`. |
| **Object Structure** | The expression tree or collection of elements where visitors are applied. |

---

## 🧩 Example Structure

