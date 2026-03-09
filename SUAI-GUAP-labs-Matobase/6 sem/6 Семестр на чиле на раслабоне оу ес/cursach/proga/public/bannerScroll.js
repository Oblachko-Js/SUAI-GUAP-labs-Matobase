function startBannerScroll(bannerContent) {
  let scrollSpeed = 1; // Скорость прокрутки (пикселей за кадр)
  let images = Array.from(bannerContent.children); // Все картинки
  let imageHeight = images[0].offsetHeight; // Высота одной картинки
  let gap = 10; // Отступ между картинками

  function scrollBanner() {
    // Получаем текущую позицию
    let currentY =
      parseFloat(
        bannerContent.style.transform
          .replace("translateY(", "")
          .replace("px)", "")
      ) || 0;

    // Двигаем вверх
    let newY = currentY - scrollSpeed;
    bannerContent.style.transform = `translateY(${newY}px)`;

    // Если верхняя картинка полностью вышла за пределы + gap
    let firstImage = images[0];
    if (Math.abs(newY) >= imageHeight + gap) {
      // Убираем её из начала списка и добавляем в конец
      bannerContent.appendChild(firstImage);
      images.push(images.shift());

      // Корректируем позицию контейнера, чтобы отступ `gap` сохранялся
      bannerContent.style.transform = `translateY(${
        newY + imageHeight + gap
      }px)`;
    }

    requestAnimationFrame(scrollBanner);
  }

  // Устанавливаем начальную позицию
  bannerContent.style.transform = "translateY(0px)";
  requestAnimationFrame(scrollBanner);
}

// Запускаем анимацию для левого и правого баннера
document.addEventListener("DOMContentLoaded", () => {
  startBannerScroll(document.querySelector(".left-banner .banner-content"));
  startBannerScroll(document.querySelector(".right-banner .banner-content"));
});
