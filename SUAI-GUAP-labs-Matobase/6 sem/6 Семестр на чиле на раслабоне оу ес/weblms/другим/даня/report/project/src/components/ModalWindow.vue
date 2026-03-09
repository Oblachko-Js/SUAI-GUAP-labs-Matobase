<!-- src/components/ModalWindow.vue -->
<template>
  <div class="modal-overlay" @click.self="close">
    <div class="modal">
      <p :class="{ success: success, error: !success }">{{ message }}</p>
      <button @click="close">Закрыть</button>
    </div>
  </div>
</template>

<script>
export default {
  props: {
    message: String,
    success: Boolean
  },
  methods: {
    close() {
      this.$emit('close');
    }
  }
};
</script>

<style scoped>
.modal-overlay {
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background: rgba(0, 0, 0, 0.5);
  display: flex;
  justify-content: center;
  align-items: center;
}

.modal {
  background: white;
  padding: 20px;
  border-radius: 5px;
  text-align: center;
  width: 300px;
}

button {
  margin-top: 10px;
  padding: 10px;
  background-color: #4CAF50;
  color: white;
  border: none;
  border-radius: 5px;
  cursor: pointer;
}

button:hover {
  background-color: #45a049;
}

.success {
  color: green;
}

.error {
  color: red;
}
</style>
