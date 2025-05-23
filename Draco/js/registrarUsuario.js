import { supabase } from './supabaseClient.js';

document.addEventListener("DOMContentLoaded", () => {
  const form = document.getElementById("registerForm");

  form.addEventListener("submit", async function (e) {
    e.preventDefault();

    const email = form.email.value;
    const username = form.username.value;
    const lastName = form.lastName?.value || null;
    const password = form.password.value;
    const confirmPassword = form.confirmPassword.value;
    const phone = form.phone?.value || null;
    const shoeSize = parseInt(form.shoeSize?.value, 10);

    if (password !== confirmPassword) {
      alert("Las contraseñas no coinciden.");
      return;
    }

    if (isNaN(shoeSize) || shoeSize <= 0) {
      alert("Por favor ingresa una talla válida.");
      return;
    }

    // 1. Crear cuenta
    const { data: signUpData, error: signUpError } = await supabase.auth.signUp({
      email,
      password,
    });

    if (signUpError) {
      alert("Error al registrar: " + signUpError.message);
      return;
    }

    alert("¡Registro exitoso!");

    // 2. Iniciar sesión
    const { data: loginData, error: loginError } = await supabase.auth.signInWithPassword({
      email,
      password,
    });

    if (loginError || !loginData.user) {
      alert("Error al iniciar sesión después del registro: " + (loginError?.message || "Usuario no obtenido"));
      return;
    }

    const userId = loginData.user.id;

    // DEBUG: Ver lo que se va a insertar
    console.log("Insertando datos:");
    console.log({
      id: userId,
      usuario: username,
      correo: email,
      apellidos: lastName,
      telefono: phone,
      talla: shoeSize,
      FechaRegistro: new Date().toISOString()
    });

    // 3. Insertar en la tabla "usuarios"
    const { error: insertError } = await supabase.from("usuarios").insert({
      id: userId,
      usuario: username,
      correo: email,
      apellidos: lastName,
      telefono: phone,
      talla: shoeSize,
      FechaRegistro: new Date().toISOString()
    });

    if (insertError) {
      console.error("Error al insertar en usuarios:", insertError);
      alert("Cuenta creada, pero hubo un error al guardar tus datos: " + insertError.message);
    } else {
      alert("¡Cuenta y perfil creados exitosamente!");
      window.location.href = "/index.html";
    }
  });
});
