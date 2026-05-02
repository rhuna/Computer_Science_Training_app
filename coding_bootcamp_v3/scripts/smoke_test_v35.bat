@echo off
echo CS Bootcamp Desktop v35 Smoke Test
if not exist docs\V35_SPLIT_TOPIC_DEEP_LESSONS.md exit /b 1
if not exist content_packs\v35_split_topic_deep_lessons_pack.md exit /b 1
if not exist examples\v35_split_topic_lessons exit /b 1
echo v35 files present.
