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
const faqData = [
  "VIT (Vishwakarma Institute of Technology) is consistently ranked among the top engineering colleges in India, but it may not be considered the best college in the world. It has an excellent reputation for its academic programs, research facilities, and industry collaborations. However, there are many other prestigious universities and colleges globally that rank higher in various international rankings.",

  "VIT is typically ranked among the top 10-15 engineering colleges in India by various national ranking agencies and surveys. In the NIRF (National Institutional Ranking Framework) rankings for 2022, VIT was ranked 10th among engineering institutes in India.",

  "Yes, VIT is accredited by the National Assessment and Accreditation Council (NAAC) with an 'A++' grade, which is the highest accreditation awarded by NAAC. It is also recognized by the University Grants Commission (UGC) and is an autonomous institute affiliated with Savitribai Phule Pune University.",

  "VIT has an impressive placement record, with over 90% of eligible students getting placed in reputable companies every year. Some of the top recruiters at VIT include companies like Amazon, Microsoft, Google, Intel, Samsung, and many others from various sectors.",

  "Admission to VIT is based on performance in national-level engineering entrance exams like JEE Main and VITEEE (VIT Engineering Entrance Exam). The eligibility criteria include meeting the minimum cut-off scores in these exams and fulfilling the required academic qualifications (typically 12th standard or equivalent).",

  "VIT has a sprawling, well-developed campus with modern infrastructure and facilities. It offers excellent academic resources, state-of-the-art laboratories, libraries, sports facilities, and amenities for a well-rounded student experience. The campus is known for its vibrant and active student community.",

  "VIT has several research centers and laboratories focused on various fields, including engineering, science, management, and humanities. It encourages student research and provides opportunities for students to work on research projects with faculty members and industry partners.",

  "VIT follows a well-structured and industry-relevant curriculum that incorporates theoretical knowledge, practical skills, and project-based learning. The teaching methodology emphasizes interactive learning, case studies, and real-world applications, making it comparable to other top engineering colleges in India Copy",

  "VIT offers various scholarships and financial aid options to support deserving students. These include merit-based scholarships, need-based scholarships, and educational loans facilitated through tie-ups with banks. The institute also provides fee waivers and concessions for economically disadvantaged students.",

  "VIT has a strong and active alumni network with chapters across India and globally. The alumni association organizes various events, mentorship programs, and career support initiatives for current students and alumni. The institute also has dedicated placement and career development cells to assist students with their professional aspirations.",

  "VIT has a vibrant student community with numerous clubs, organizations, and societies catering to diverse interests such as sports, cultural activities, technical clubs, entrepreneurship cells, and more. Students have ample opportunities to participate in extracurricular activities and develop their skills and interests beyond academics.",

  "VIT has a strong focus on promoting entrepreneurship and innovation. It has dedicated centers and incubation facilities to support student startups and entrepreneurial ventures. The institute organizes various entrepreneurship development programs, workshops, and competitions to encourage an entrepreneurial mindset among students.",

  "VIT has a diverse and inclusive student community, with students from various states and countries studying on its campuses. The institute actively promotes international collaborations and attracts students from across the globe, creating a multicultural environment for learning and personal growth.",

  "VIT consistently ranks among the top institutes in India in terms of campus placements and average salary packages offered to its graduates. The average salary packages offered to VIT graduates are highly competitive and comparable to those offered at other top engineering colleges in the country.",
];
const search = (str, i, root) => {
  console.log(document.getElementById("list").innerText);
  if (
    document
      .getElementById("list")
      .innerText.includes(faqData.map((answ) => answ))
  ) {
    document.getElementById("list").innerHTML = "";
  }

  if (i === str.length) {
    return root.words;
  }

  if (!root.map[str[i]]) {
    return [];
  }

  return search(str, i + 1, root.map[str[i]]);
};
