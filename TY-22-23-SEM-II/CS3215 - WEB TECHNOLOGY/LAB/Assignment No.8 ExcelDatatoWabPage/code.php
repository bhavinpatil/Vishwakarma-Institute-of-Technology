<?php
// Connect to the database
$conn = mysqli_connect("localhost", "bhavin", "bhavin", "database1");

// Query the database
$result = mysqli_query($conn, "SELECT * FROM pokemon");

// Generate the table headers dynamically
echo "<table>";
echo "<tr>";
foreach (mysqli_fetch_fields($result) as $field) {
    echo "<th>" . $field->name . "</th></th>";
}
echo "</tr>";

// Output the data as a dynamic HTML table
while ($row = mysqli_fetch_assoc($result)) {
    echo "<tr>";
    foreach ($row as $value) {
        echo "<td>" . $value . "</td>";
    }
    echo "</tr>";
}
echo "</table>";

// Close the database connection
mysqli_close($conn);
?>
