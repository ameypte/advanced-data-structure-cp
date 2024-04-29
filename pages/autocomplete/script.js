class makeNode {
  constructor(character) {
    this.ch = character;
    this.isTerminal = false;
    this.map = {};
    this.words = [];
  }
}

const add = (str, i, root) => {
  if (i === str.length) {
    console.log(root.words);
    return;
  }
  if (!root.map[str[i]]) {
    console.log(root.map[str[i]]);
    root.map[str[i]] = new makeNode(str[i]);
  }
  root.words.push(str);
  add(str, i + 1, root.map[str[i]]);
};

const search = (str, i, root) => {
  if (i === str.length) {
    return root.words;
  }

  if (!root.map[str[i]]) {
    return [];
  }

  return search(str, i + 1, root.map[str[i]]);
};
