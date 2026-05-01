CREATE TABLE IF NOT EXISTS verification_tokens (token TEXT NOT NULL);
DELETE FROM verification_tokens;
INSERT INTO verification_tokens(token) VALUES ('PASS_RAG_DESIGN_DOC');
