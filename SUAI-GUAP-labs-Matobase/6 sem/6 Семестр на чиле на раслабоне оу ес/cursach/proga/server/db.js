const { Pool } = require("pg");

const pool = new Pool({
  user: "andrejpancenko",
  host: "localhost",
  database: "habit_tracker_rpg",
  password: "",
  port: 5432,
});

module.exports = {
  query: (text, params) => pool.query(text, params),
  connect: () => {
    return pool.connect();
  },
};
