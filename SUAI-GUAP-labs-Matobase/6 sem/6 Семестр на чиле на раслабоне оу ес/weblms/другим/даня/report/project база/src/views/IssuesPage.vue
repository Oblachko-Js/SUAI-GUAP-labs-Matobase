<!-- src/views/IssuesPage.vue -->
<template>
    <div class="issues-page">
        <h1 class="fade-in">Искажения и проблемы в линиях связи</h1>
        <p class="centered-text fade-in">Ключевые источники искажений канала и практические способы их минимизации.</p>

        <!-- Карусель изображений -->
        <section class="carousel-section fade-in">
            <div class="carousel">
                <img :src="require(`@/assets/${carouselImages[currentImageIndex]}`)" alt="Искажения линий связи" class="carousel-image"/>
            </div>

            <!-- Кнопки управления каруселью -->
            <div class="carousel-controls">
                <button @click="prevImage" class="carousel-btn left-btn">←</button>
                <button @click="nextImage" class="carousel-btn right-btn">→</button>
            </div>
        </section>

        <!-- Текстовое описание проблем -->
        <section class="text-description fade-in">
            <h2>Основные виды искажений</h2>
            <p>
                <strong>Кросс‑наводки (NEXT/FEXT)</strong>: электромагнитное влияние соседних пар/каналов, повышает уровень шума и BER в медных линиях. Борьба: экранирование, витая пара высокой категории, корректная разводка, профили спектра.
            </p>
            <p>
                <strong>Многолучевость и замирания</strong> (радиоканал): интерференция сигналов разных путей приводит к селективному замиранию по частоте/времени. Борьба: OFDM, MIMO, интерливинг, частотное/временное разнообразие.
            </p>
            <p>
                <strong>Дисперсия</strong> (оптоволокно): хроматическая и модовая дисперсия расширяют импульсы, вызывая межсимвольные искажения. Борьба: одномодовое волокно, узкополосные источники, компенсация дисперсии.
            </p>
            <p>
                <strong>Отражения и несогласование</strong>: неправильное согласование импедансов вызывает стоячие волны и искажения. Борьба: согласующие элементы, качественные коннекторы, контроль КСВ/Return Loss.
            </p>
            <p>
                <strong>Нелинейности</strong>: насыщение усилителей/лазеров, интермодуляция создают дополнительные частотные компоненты. Борьба: линейные режимы, предискажение, контроль мощности.
            </p>
            <p>
                <strong>Помехи</strong>: импульсные/узкополосные помехи повышают BER. Борьба: экранирование, частотное планирование, фильтрация, кодирование с исправлением ошибок.
            </p>
            <p>
                <strong>Температурная и временная нестабильность</strong>: дрейф параметров линий/элементов ухудшает согласование и синхронизацию. Борьба: температурная компенсация, калибровка, резервирование.
            </p>
            <p>
                Для минимизации искажений применяют экранирование, корректирующее кодирование (FEC), адаптивную модуляцию, эквалайзеры, MIMO/OFDM, согласование, компенсацию дисперсии, а также грамотную топологию и заземление.
            </p>
            <p>
                При проектировании линии важно балансировать требования: полоса/скорость, BER, дальность, устойчивость к помехам и стоимость. Правильный выбор среды и параметров канала обеспечивает требуемое качество сервиса.
            </p>
        </section>

        <!-- Текст для привлечения внимания к опросу -->
        <div class="survey-prompt fade-in">
            <p>Поделитесь опытом: какие искажения канала вы встречали и как решали?</p>
        </div>

        <!-- Форма для сбора информации о проблемах -->
        <form @submit.prevent="handleSubmit">
            <div>
                <label for="problem">Какие искажения/проблемы вы наблюдали в линии связи?</label>
                <textarea
                    id="problem"
                    v-model="form.problem"
                    required
                    placeholder="Опишите искажения, условия и тип среды"
                ></textarea>
            </div>

            <div>
                <label for="impact">Как искажения влияли на BER/скорость/задержку?</label>
                <textarea
                    id="impact"
                    v-model="form.impact"
                    required
                    placeholder="Опишите влияние на качество канала и сервис"
                ></textarea>
            </div>

            <div>
                <label for="solution">Какие меры помогли снизить искажения?</label>
                <textarea
                    id="solution"
                    v-model="form.solution"
                    required
                    placeholder="Опишите меры: экранирование, кодирование, эквалайзер и т. п."
                ></textarea>
            </div>

            <button type="submit">Отправить</button>
        </form>

        <!-- Кнопка для перехода на страницу заключения -->
        <div class="buttons">
            <button @click="goToPage('/conclusion')">Перейти к выводам</button>
        </div>

        <!-- Модальное окно -->
        <ModalWindow v-if="showModal" :message="modalMessage" :success="isSuccess" @close="closeModal"/>
    </div>
</template>

<script>
import ModalWindow from '../components/ModalWindow.vue';

export default {
    name: 'IssuesPage',
    components: {
        ModalWindow
    },
    data() {
        return {
            form: {
                problem: '',
                impact: '',
                solution: ''
            },
            showModal: false,
            modalMessage: '',
            isSuccess: false,
            // Массив картинок для карусели
            carouselImages: [
                'crosstalk-diagram.png',
                'multipath-fading.png',
                'fiber-dispersion.png'
            ],
            currentImageIndex: 0, // Индекс текущего изображения
        };
    },
    methods: {
        nextImage() {
            // Переход к следующему изображению
            this.currentImageIndex = (this.currentImageIndex + 1) % this.carouselImages.length;
        },
        prevImage() {
            // Переход к предыдущему изображению
            this.currentImageIndex = (this.currentImageIndex - 1 + this.carouselImages.length) % this.carouselImages.length;
        },
        handleSubmit() {
            if (!this.form.problem || !this.form.impact || !this.form.solution) {
                this.modalMessage = 'Пожалуйста, заполните все поля!';
                this.isSuccess = false;
                this.showModal = true;
                return;
            }

            this.modalMessage = 'Спасибо за ваше предложение по решению проблемы!';
            this.isSuccess = true;
            this.showModal = true;
            this.clearForm();
        },
        closeModal() {
            this.showModal = false;
        },
        clearForm() {
            this.form.problem = '';
            this.form.impact = '';
            this.form.solution = '';
        },
        goToPage(page) {
            this.$router.push(page);
            window.scrollTo({ top: 0, behavior: 'smooth' }); // Прокрутка наверх
        },
        autoChangeImage() {
            setInterval(() => {
                this.nextImage();
            }, 5000); // Меняем картинку каждые 5 секунд
        }
    },
    mounted() {
        this.autoChangeImage(); // Запускаем авто-смену изображений при монтировании компонента
    }
};
</script>

<style scoped>
/* Анимация плавного появления */
@keyframes fadeIn {
  from {
    opacity: 0;
    transform: translateY(20px);
  }
  to {
    opacity: 1;
    transform: translateY(0);
  }
}

/* Применение анимации к элементам */
.fade-in {
  animation: fadeIn 1.5s ease-out;
}

/* Добавленный стиль для блока с текстом для привлечения внимания */
.survey-prompt {
    margin-top: 20px;
    background-color: #f4f4f4;
    padding: 10px 20px;
    border-radius: 5px;
    font-size: 1.2rem;
    color: #d9534f;
    text-align: center;
    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
    display: flex;
    justify-content: center;
    align-items: center;
    height: 60px;
}

.survey-prompt p {
    margin: 0;
    font-weight: bold;
    color: #d9534f;
}

/* Стиль страницы */
.issues-page {
    margin-top: 250px;
    text-align: center;
    padding: 20px;
    max-width: 1200px;
    margin: 0 auto;
    min-height: 100vh;
    overflow: auto;
    font-family: 'Arial', sans-serif;
    line-height: 1.6;
}

h1 {
    font-size: 2rem;
    color: #333;
    margin-bottom: 20px;
}

p {
    font-size: 1.1rem;
    color: #555;
    text-align: justify;
    margin-bottom: 15px;
}

strong {
    font-weight: bold;
    color: #2d3d55;
}

.carousel-section {
    margin-bottom: 40px;
    position: relative;
}

.carousel {
    display: flex;
    justify-content: center;
    align-items: center;
    overflow: hidden;
    position: relative;
    height: 300px;
}

.carousel-image {
    width: 100%;
    max-width: 500px;
    height: 100%;
    object-fit: cover;
    border-radius: 10px;
}

.carousel-controls {
    position: absolute;
    top: 50%;
    left: 0;
    right: 0;
    display: flex;
    justify-content: space-between;
    align-items: center;
    transform: translateY(-50%);
    width: 100%;
}

.carousel-btn {
    background-color: rgba(0, 0, 0, 0.5);
    color: white;
    padding: 10px;
    font-size: 18px;
    border: none;
    border-radius: 50%;
    cursor: pointer;
    transition: background-color 0.3s;
}

.carousel-btn:hover {
    background-color: rgba(0, 0, 0, 0.7);
}

.carousel-btn.left-btn {
    margin-left: 20px;
}

.carousel-btn.right-btn {
    margin-right: 20px;
}

.text-description {
    margin-top: 20px;
}

form {
    margin-top: 20px;
    display: flex;
    flex-direction: column;
    max-width: 800px;
    margin: 0 auto;
}

form div {
    margin-bottom: 10px;
}

label {
    font-size: 14px;
    margin-bottom: 5px;
    color: #333;
}

textarea {
    width: 100%;
    padding: 8px;
    font-size: 13px;
    border: 1px solid #ccc;
    border-radius: 5px;
    height: 80px;
    resize: vertical;
}

.centered-text {
    text-align: center;
}

button {
    padding: 8px 12px;
    background-color: #4CAF50;
    color: white;
    font-size: 14px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    margin-top: 10px;
}

button:hover {
    background-color: #45a049;
}

/* Стиль для кнопки "Перейти к заключению" */
.buttons {
    margin-top: 20px;
}

.buttons button {
    padding: 12px 24px;
    font-size: 1.1rem;
    font-weight: bold;
    color: #1e3c72;
    background-color: #ffffff;
    border: none;
    border-radius: 8px;
    cursor: pointer;
    transition: background-color 0.3s ease, transform 0.3s ease;
    margin: 10px;
    display: inline-block;
}

.buttons button:hover {
    background-color: #e6e6e6;
    transform: translateY(-5px);
}

@media (max-width: 1200px) {
    .issues-page {
        padding: 15px;
        margin-top: 160px;
    }
    h1 {
        font-size: 1.8rem;
    }
}

@media (max-width: 800px) {
    .carousel-image {
        max-width: 100%;
        margin-top: 160px;
    }
}

@media (max-width: 550px) {
    h1 {
        font-size: 1.6rem;
        margin-top: 20px;
    }
    p {
        font-size: 1rem;
    }
}
</style>
