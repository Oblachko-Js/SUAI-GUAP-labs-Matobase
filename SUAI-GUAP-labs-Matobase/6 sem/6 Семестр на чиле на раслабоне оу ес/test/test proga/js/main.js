document.addEventListener("DOMContentLoaded", function () {
  const contactForm = document.getElementById("contactForm");
  if (contactForm) {
    contactForm.addEventListener("submit", function (e) {
      e.preventDefault();
      const formData = new FormData(contactForm);
      const data = Object.fromEntries(formData);

      // Here you would typically send the data to your server
      alert("Thank you for your message! We will get back to you soon.");
      contactForm.reset();
    });
  }
});
