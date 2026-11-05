// Shared helpers for the prose sheets (.typ snippets); not a snippet.
#let sans = sys.inputs.at("sans", default: "Helvetica Neue")
// A theorem or technique: bold sans name, then the text.
#let t(name, body) = [#text(font: sans, weight: "bold", size: 6.5pt, name) #h(2pt) #body]
// A section row spanning both columns of a formula table.
#let sec(title) = table.cell(colspan: 2, inset: (top: 4pt, bottom: 1.5pt, x: 2pt),
  text(font: sans, weight: "bold", size: 6.3pt, tracking: 0.05em, upper(title)))
