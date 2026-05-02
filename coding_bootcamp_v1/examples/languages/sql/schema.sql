CREATE TABLE IF NOT EXISTS words (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    word TEXT NOT NULL,
    count INTEGER NOT NULL
);

INSERT INTO words (word, count) VALUES ('sql', 1), ('starter', 1), ('sql', 1);

SELECT word, SUM(count) AS total
FROM words
GROUP BY word
ORDER BY total DESC;
