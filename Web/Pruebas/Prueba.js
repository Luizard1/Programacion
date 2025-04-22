let currentIndex = 0;
const images = [
    '../Imagenes/ModeloHombre3.jpg',
    '../Imagenes/ModeloVariosHombres1-removebg-preview.png',  // Agrega más imágenes aquí
    '../Imagenes/ModeloVariosHombres2-removebg-preview.png'
];
const heroImage = document.querySelector('.hero-image');

document.querySelector('.next-button').addEventListener('click', function() {
    currentIndex = (currentIndex + 1) % images.length;
    heroImage.style.opacity = 0; // Hacemos que la imagen desaparezca para el cambio
    setTimeout(() => {
        heroImage.src = images[currentIndex]; // Cambiamos la imagen
        heroImage.style.opacity = 1; // Volvemos a mostrarla
    }, 500); // Tiempo para la transición de opacidad
});

document.querySelector('.prev-button').addEventListener('click', function() {
    currentIndex = (currentIndex - 1 + images.length) % images.length;
    heroImage.style.opacity = 0; // Hacemos que la imagen desaparezca para el cambio
    setTimeout(() => {
        heroImage.src = images[currentIndex]; // Cambiamos la imagen
        heroImage.style.opacity = 1; // Volvemos a mostrarla
    }, 500); // Tiempo para la transición de opacidad
});
