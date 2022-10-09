# ocrpi
OCR Pseudocode Interpreter

OCRPI is an interpreter for the OCR pseudocode syntax described on page 31 of the [A Level Specification](https://www.ocr.org.uk/Images/170844-specification-accredited-a-level-gce-computer-science-h446.pdf). It aims to be fully compliant with this description to act as a tool for learners to interactively test their knowledge of the syntax. The design focuses on friendly, helpful error messages, allowing learners to improve their understanding. Speed of execution is not initially a priority but later versions will improve on this, potentialy turning it into something closer to a compiler.

---

As the pseudocode description isn't a de-facto language spec, I've made some assumptions:

- Variable names can contain any alphanumeric characters and underscores, but may not start with a number
- String literals are denoted with double quotes ONLY and are never multi-line
- Variables (when I get there) and parameters are **dynamically typed**, although this will eventually be a configurable option