document.addEventListener("DOMContentLoaded", () => {
  const burgerMenu = document.querySelector(".burger-menu");
  const navLinks = document.querySelector(".nav-links");
  const navOverlay = document.querySelector(".nav-overlay");
  const navLinksItems = document.querySelectorAll(".nav-links a");

  // Toggle menu
  burgerMenu.addEventListener("click", () => {
    burgerMenu.classList.toggle("active");
    navLinks.classList.toggle("active");
    navOverlay.classList.toggle("active");
    document.body.style.overflow = navLinks.classList.contains("active")
      ? "hidden"
      : "";
  });

  // Close menu when clicking overlay
  navOverlay.addEventListener("click", () => {
    burgerMenu.classList.remove("active");
    navLinks.classList.remove("active");
    navOverlay.classList.remove("active");
    document.body.style.overflow = "";
  });

  // Close menu when clicking a link
  navLinksItems.forEach((link) => {
    link.addEventListener("click", () => {
      burgerMenu.classList.remove("active");
      navLinks.classList.remove("active");
      navOverlay.classList.remove("active");
      document.body.style.overflow = "";
    });
  });

  // Close menu on window resize if open
  window.addEventListener("resize", () => {
    if (window.innerWidth > 992 && navLinks.classList.contains("active")) {
      burgerMenu.classList.remove("active");
      navLinks.classList.remove("active");
      navOverlay.classList.remove("active");
      document.body.style.overflow = "";
    }
  });
});
