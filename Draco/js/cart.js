// js/cart.js
import { products } from "./products.js";

document.addEventListener("DOMContentLoaded", () => {
  const itemsDiv      = document.getElementById("cart-items");
  const totalSpan     = document.getElementById("cart-total");
  const checkoutBtn   = document.getElementById("checkout");
  const methodCode    = document.getElementById("method-code");
  const methodCard    = document.getElementById("method-card");
  const paySection    = document.getElementById("payment-method");
  const codeSection   = document.getElementById("payment-code");
  const cardSection   = document.getElementById("payment-card");
  const generatedCode = document.getElementById("generated-code");
  const confirmCode   = document.getElementById("confirm-code");
  const cardForm      = document.getElementById("card-form");

  // 1. Cargar carrito
  const cart = JSON.parse(localStorage.getItem("cart")) || [];

  // 2. Mostrar productos y calcular total
  let total = 0;
  cart.forEach((prodId, idx) => {
    const p = products[prodId];
    if (!p) return;
    const priceNum = parseFloat(p.price.replace(/[^0-9.]/g, ""));
    total += priceNum;

    const div = document.createElement("div");
    div.className = "cart-item";
    div.innerHTML = `
      <img src="${p.images[0]}" alt="${p.title}" width="80" />
      <div class="cart-info">
        <h2>${p.title}</h2>
        <p>${p.price}</p>
      </div>
      <button class="remove-btn" data-idx="${idx}">Eliminar</button>
    `;
    itemsDiv.append(div);
  });
  totalSpan.textContent = `MXN$ ${total.toFixed(2)}`;

  // 3. Eliminar producto
  itemsDiv.addEventListener("click", e => {
    if (!e.target.matches(".remove-btn")) return;
    const idx = Number(e.target.dataset.idx);
    cart.splice(idx, 1);
    localStorage.setItem("cart", JSON.stringify(cart));
    location.reload();
  });

  // 4. Al hacer clic en “Proceder a Pagar”
  checkoutBtn.addEventListener("click", () => {
    if (cart.length === 0) {
      alert("Tu carrito está vacío.");
      return;
    }
    // Mostrar opciones de pago
    paySection.style.display  = "block";
    checkoutBtn.disabled      = true;
  });

  // 5. Cuando eligen “Pagar con código”
  methodCode.addEventListener("change", () => {
    if (!methodCode.checked) return;
    // Generar código aleatorio
    const code = "COD-" + Math.random().toString(36).substr(2, 8).toUpperCase();
    generatedCode.textContent = code;
    codeSection.style.display = "block";
    cardSection.style.display = "none";
  });

  // 6. Cuando eligen “Pagar con tarjeta”
  methodCard.addEventListener("change", () => {
    if (!methodCard.checked) return;
    cardSection.style.display = "block";
    codeSection.style.display = "none";
  });

  // 7. Confirmar pago por código
  confirmCode.addEventListener("click", () => {
    alert(`✅ Pago con código procesado por MXN$ ${total.toFixed(2)}. ¡Gracias!`);
    localStorage.removeItem("cart");
    location.reload();
  });

  // 8. Procesar pago con tarjeta (simulado)
  cardForm.addEventListener("submit", e => {
    e.preventDefault();
    alert(`✅ Pago con tarjeta procesado por MXN$ ${total.toFixed(2)}. ¡Gracias!`);
    localStorage.removeItem("cart");
    location.reload();
  });
});
