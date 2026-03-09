document.addEventListener("DOMContentLoaded", () => {
  // Get all navigation links
  const navLinks = document.querySelectorAll(".nav-links a");

  // Add click event listener to each link
  navLinks.forEach((link) => {
    link.addEventListener("click", async (e) => {
      e.preventDefault();

      // Get the target page URL
      const targetUrl = link.getAttribute("href");

      // Update active link
      navLinks.forEach((l) => l.classList.remove("active"));
      link.classList.add("active");

      try {
        // Fetch the target page content
        const response = await fetch(targetUrl);
        const html = await response.text();

        // Create a temporary element to parse the HTML
        const parser = new DOMParser();
        const doc = parser.parseFromString(html, "text/html");

        // Get the main content
        const newContent = doc.querySelector(".content");

        // Add fade-out effect to current content
        const currentContent = document.querySelector(".content");
        currentContent.style.opacity = "0";

        // Wait for fade-out animation
        setTimeout(() => {
          // Update the content
          currentContent.innerHTML = newContent.innerHTML;

          // Update page title
          document.title = doc.title;

          // Update URL without reload
          history.pushState({}, "", targetUrl);

          // Add fade-in effect
          currentContent.style.opacity = "1";
        }, 300);
      } catch (error) {
        console.error("Error loading page:", error);
      }
    });
  });

  // Handle browser back/forward buttons
  window.addEventListener("popstate", async () => {
    const currentPath = window.location.pathname;
    const targetUrl = currentPath === "/" ? "home.html" : currentPath;

    try {
      const response = await fetch(targetUrl);
      const html = await response.text();
      const parser = new DOMParser();
      const doc = parser.parseFromString(html, "text/html");

      const newContent = doc.querySelector(".content");
      const currentContent = document.querySelector(".content");

      currentContent.style.opacity = "0";

      setTimeout(() => {
        currentContent.innerHTML = newContent.innerHTML;
        document.title = doc.title;

        // Update active link
        navLinks.forEach((link) => {
          link.classList.remove("active");
          if (link.getAttribute("href") === targetUrl) {
            link.classList.add("active");
          }
        });

        currentContent.style.opacity = "1";
      }, 300);
    } catch (error) {
      console.error("Error loading page:", error);
    }
  });
});
