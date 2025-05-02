let currentIndex = 0;
const images = [
    'Media/Imagenes/Zapatos/BussinesMan/CarruselBM2.png',
    'Media/Imagenes/Zapatos/NocturneDandy/CarruselND1.png',  // Agrega más imágenes aquí
    'Media/Imagenes/Zapatos/ModernHeritage/CarruselMH1.png'
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
