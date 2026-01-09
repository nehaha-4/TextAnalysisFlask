function analyzeText() {
    let text = document.getElementById("textInput").value.toLowerCase();
    let keyword = document.getElementById("keyword").value.toLowerCase();
    let k = parseInt(document.getElementById("kValue").value);

    // Remove punctuation
    text = text.replace(/[^a-z0-9 ]/g, "");

    let words = text.split(" ");
    let freq = {};

    // Frequency count (DSA logic)
    for (let w of words) {
        if (w === "") continue;
        freq[w] = (freq[w] || 0) + 1;
    }

    // Convert object to array for sorting
    let freqArray = [];
    for (let key in freq) {
        freqArray.push([key, freq[key]]);
    }

    // Sort descending by frequency
    freqArray.sort((a, b) => b[1] - a[1]);

    // Output text
    let output = "<b>Word Frequencies:</b><br>";
    freqArray.forEach(item => {
        output += `${item[0]} : ${item[1]}<br>`;
    });

    // Prepare data for bar chart
    let chartWords = [];
    let chartCounts = [];

    if (!isNaN(k)) {
        output += `<br><b>Top ${k} Words:</b><br>`;
        for (let i = 0; i < Math.min(k, freqArray.length); i++) {
            output += `${freqArray[i][0]} : ${freqArray[i][1]}<br>`;
            chartWords.push(freqArray[i][0]);
            chartCounts.push(freqArray[i][1]);
        }
    } else {
        // Default: top 5
        for (let i = 0; i < Math.min(5, freqArray.length); i++) {
            chartWords.push(freqArray[i][0]);
            chartCounts.push(freqArray[i][1]);
        }
    }

    // Keyword search
    if (keyword) {
        let found = freq[keyword] || 0;
        output += `<br><b>Keyword '${keyword}' found ${found} times</b>`;
    }

    document.getElementById("output").innerHTML = output;

    // Draw bar chart
    drawChart(chartWords, chartCounts);
}

/* BAR CHART FUNCTION */
function drawChart(words, counts) {
    const ctx = document.getElementById("freqChart").getContext("2d");

    if (window.myChart) {
        window.myChart.destroy();
    }

    window.myChart = new Chart(ctx, {
        type: "bar",
        data: {
            labels: words,
            datasets: [{
                label: "Word Frequency",
                data: counts,
                backgroundColor: "#4e73df"
            }]
        },
        options: {
            responsive: true,
            scales: {
                y: {
                    beginAtZero: true
                }
            }
        }
    });
}

/* FILE UPLOAD FUNCTION */
function readFile() {
    const fileInput = document.getElementById("fileInput");
    const file = fileInput.files[0];

    if (!file) {
        alert("Please select a .txt file");
        return;
    }

    const reader = new FileReader();

    reader.onload = function (e) {
        document.getElementById("textInput").value = e.target.result;
    };

    reader.readAsText(file);
}
