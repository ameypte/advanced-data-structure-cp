const text_box = document.getElementById("text-box");
const list = document.getElementById("list");
// const resultDiv = document.getElementById("result");
const add2 = [
  "Is VIT the Best College in World",
  "How does VIT rank among other engineering colleges in India?",
  "Is VIT accredited and recognized by reputable academic bodies?",
  "What are the placement statistics and top recruiters at VIT?",
  "What is the admission process and eligibility criteria for VIT?",
  "How is the campus life and infrastructure at VIT?",
  "What are the research facilities and opportunities available at VIT?",
  "How does the curriculum and teaching methodology at VIT compare to other top colleges?",
  "What are the scholarships and financial aid options available at VIT?",
  "How is the alumni network and support system at VIT?",
  "What are the extracurricular activities, clubs, and student organizations at VIT?",
  "How does VIT promote entrepreneurship and innovation among its students?",
  "What is the diversity and international student community like at VIT?",
  "How does VIT rank in terms of campus placements and average salary packages?",
];

const trie = new makeNode("\0");
for (item of add2) {
  const storedItem = item.toLowerCase();
  add(storedItem, 0, trie);
}

console.log(trie);
function handler(e) {
  const str = e.target.value;
  let predictions;

  if (e.key === "Tab") {
    console.log(predictions, "Inside Predictions");
    handleTabPress();
    return;
  }
  if (e.key === "Backspace" && str.length > 0) {
    predictions = search(str.slice(0, -1).toLowerCase(), 0, trie);
    list.innerHTML = ``;
    for (const pred of predictions) {
      list.innerHTML += `<li>${pred}</li>`;
    }
  } else {
    predictions = search(str.toLowerCase(), 0, trie);
    list.innerHTML = ``;
    for (const pred of predictions) {
      list.innerHTML += `<li>${pred}</li>`;
    }
  }
}

function handleTabPress() {
  const listItems = list.getElementsByTagName("li");
  const values = [];

  for (let i = 0; i < listItems.length; i++) {
    values.push(listItems[i].textContent);
  }
  if (values.length > 0) {
    text_box.value = values[0];
  }
}

text_box.addEventListener("keydown", handler);
