// Team notebook. Build with `python3 build.py` (it writes build/data.json first).
//
// Layout model: A4 landscape, three fixed columns per page. Every snippet is an
// unbreakable box. The packer below measures each box and decides column by
// column what goes where, so nothing is ever split across a column or page
// (except a snippet taller than a whole column, which is cut at blank lines).

#let cfg = toml("notebook.toml")
#let chapters = json("build/data.json")
#let L = cfg.layout

#let code-size = L.code_size * 1pt
#let text-size = L.text_size * 1pt
#let title-size = L.title_size * 1pt
#let mx = L.margin_x * 1mm
#let mt = L.margin_top * 1mm
#let mb = L.margin_bottom * 1mm
#let gutter = L.gutter * 1mm
#let gap = L.gap * 1pt
#let window = L.window
#let head-gap = 4pt

#let page-w = 297mm
#let page-h = 210mm
#let col-w = (page-w - 2 * mx - 2 * gutter) / 3
#let col-h = page-h - mt - mb

#let mono = ("JetBrainsMonoNL NFM", "DejaVu Sans Mono")
#let sans = sys.inputs.at("sans", default: "Helvetica Neue") // chosen by build.py
#let serif = ("New Computer Modern",)
#let gray = luma(105)

#set document(title: cfg.title + " notebook", author: cfg.team)
#set page(width: page-w, height: page-h, margin: (x: mx, top: mt, bottom: mb), header-ascent: 2.6mm)
#set text(font: serif, size: text-size, hyphenate: false)
#set par(leading: 0.42em, spacing: 0.5em)
#set block(spacing: 0pt)
#set raw(theme: "print.tmTheme", tab-size: 2)
#show raw: set text(font: mono, size: code-size)
#show raw.where(block: true): set par(leading: 0.36em)
#show raw.where(block: false): set text(size: code-size * 0.9)

// ---------------------------------------------------------------- pieces

#let md(s) = eval(s, mode: "markup")
#let key(k) = text(font: sans, weight: "bold", size: 5.8pt, tracking: 0.05em, upper(k))
#let col-label(k) = str(calc.quo(k, 3) + 1) + ("a", "b", "c").at(calc.rem(k, 3))

// A code listing; lines listed in `marks` (1-based, shifted by `off`) are the
// ones meant to be edited and get a gray background.
#let listing(code, lang, marks, off: 0, dotted: false) = {
  show raw.line: l => if (l.number + off) in marks {
    highlight(fill: luma(218), top-edge: "ascender", bottom-edge: "descender", extent: 0.6pt, l)
  } else { l }
  let rule = if dotted { (paint: luma(150), thickness: 0.7pt, dash: "dotted") } else { 0.6pt + luma(170) }
  block(width: 100%, stroke: (left: rule), inset: (left: 3.5pt, top: 1pt, bottom: 1pt),
    raw(code, lang: lang, block: true))
}

#let hash-tag(h) = text(font: mono, size: 5.5pt, weight: "bold", h)

#let snippet(it, part: 0, code: none, uses: true, off: 0) = {
  let code = if code == none { it.code } else { code }
  let uses = uses and it.at("uses", default: "") != ""
  let title = text(font: sans, weight: "bold", size: title-size, it.title)
  if part > 0 {
    title = [#title #text(font: sans, size: title-size - 1.5pt, fill: gray)[(continued)]]
  }
  let tag = if it.hash != "" {
    text(font: mono, size: 5.5pt, fill: gray)[#it.file #h(1.5pt) #text(fill: black, weight: "bold", it.hash)]
  } else if it.kind == "code" {
    text(font: mono, size: 5.5pt, fill: gray, it.file)
  }
  let body = ()
  if part == 0 {
    if it.description != "" { body.push(md(it.description)) }
    let facts = ()
    if it.time != "" { facts.push([#key("Time") #h(1.5pt) #md(it.time)]) }
    if it.memory != "" { facts.push([#key("Memory") #h(1.5pt) #md(it.memory)]) }
    if it.needs != "" { facts.push([#key("Needs") #h(1.5pt) #raw(it.needs)]) }
    if facts.len() > 0 { body.push(facts.join(h(9pt))) }
    if it.usage != "" {
      body.push(grid(
        columns: (auto, 1fr), column-gutter: 4pt, align: (left + horizon, left),
        key("Usage"), raw(it.usage, lang: it.lang, block: true),
      ))
    }
  }
  block(width: 100%, breakable: false, {
    grid(columns: (1fr, auto), column-gutter: 4pt, align: (left + bottom, right + bottom), title, tag)
    v(1.6pt)
    line(length: 100%, stroke: 0.7pt)
    v(2.6pt)
    for b in body {
      block(width: 100%, b)
      v(2.6pt)
    }
    if it.kind == "typ" {
      include (it.path)
    } else if code != "" {
      listing(code, it.lang, it.marks, off: off)
    }
    if uses {
      if code != "" { v(3.5pt) }
      grid(columns: (1fr, auto), align: (left + bottom, right + bottom), key("Uses"), hash-tag(it.uses_hash))
      v(1.5pt)
      listing(it.uses, it.lang, it.uses_marks, dotted: true)
    }
  })
}

#let chapter-head(ci) = block(width: 100%, fill: black, inset: (x: 3.5pt, y: 3pt), text(
  font: sans, weight: "bold", size: 7.5pt, fill: white, tracking: 0.08em,
)[#upper(chapters.at(ci).name) #h(1fr) #str(ci + 1)])

#let toc(labels) = {
  let lbl(k) = text(font: mono, weight: "bold", size: 6.5pt,
    if labels == none { "00a" } else { labels.at(k, default: "?") })
  text(font: sans, weight: "bold", size: 15pt, cfg.team)
  v(3pt)
  text(font: sans, size: 7.5pt, fill: gray)[#cfg.university #h(2pt)·#h(2pt) #cfg.title]
  v(2pt)
  text(size: 7pt, cfg.members.join([ #h(2pt)·#h(2pt) ]))
  v(5pt)
  line(length: 100%, stroke: 0.7pt)
  for (ci, ch) in chapters.enumerate() {
    v(5.5pt)
    text(font: sans, weight: "bold", size: 6.5pt, tracking: 0.06em)[#(ci + 1) #h(2pt) #upper(ch.name)]
    v(2.5pt)
    let cells = ch.items.enumerate().map(((ii, it)) => [#it.title #box(width: 1fr,
      repeat(text(fill: luma(175))[.#h(1.2pt)])) #lbl(str(ci) + "-" + str(ii))])
    grid(columns: (1fr, 1fr), column-gutter: 9pt, row-gutter: 2.4pt, ..cells)
  }
}

// ---------------------------------------------------------------- packing

#let mh(c) = measure(block(width: col-w, c)).height

#let col-used(col) = {
  let u = 0pt
  for (i, e) in col.enumerate() {
    if i > 0 { u += if col.at(i - 1).kind == "chapter" { head-gap } else { gap } }
    u += e.h
  }
  u
}

// Returns a list of columns; each column is a list of elements
// (kind: "toc" | "chapter" | "item", h: height, ...).
#let pack() = {
  let toc-h = mh(toc(none))
  let hdr-h = mh(chapter-head(0))
  let cap = col-h - hdr-h - head-gap

  let units = ()
  for (ci, ch) in chapters.enumerate() {
    let us = ()
    for (ii, it) in ch.items.enumerate() {
      let unit(part, code, uses, off, pinned, brk) = (
        ci: ci, ii: ii, part: part, code: code, uses: uses, off: off,
        h: mh(snippet(it, part: part, code: code, uses: uses, off: off)),
        pinned: pinned, brk: brk, extra: (),
      )
      let start = us.len()
      let h = mh(snippet(it))
      if h <= cap or it.kind != "code" {
        us.push((ci: ci, ii: ii, part: 0, code: none, uses: true, off: 0, h: h, pinned: false,
          brk: false, extra: ()))
      } else {
      let has-uses = it.uses != ""
      // Too tall: first try moving the Uses block into its own box.
      if has-uses and mh(snippet(it, uses: false)) <= cap {
        us.push(unit(0, none, false, 0, true, false))
        us.push(unit(1, "", true, 0, true, false))
      } else {
      // Still too tall: cut the code at blank lines, greedily.
      let segs = ()
      let cur = ()
      for l in it.code.split("\n") {
        cur.push(l)
        if l.trim() == "" { segs.push(cur); cur = () }
      }
      if cur.len() > 0 { segs.push(cur) }
      let parts = ()
      let acc = ()
      for s in segs {
        let trial = acc + s
        if acc.len() > 0 and mh(snippet(it, part: parts.len(), code: trial.join("\n").trim("\n"), uses: false)) > cap {
          parts.push(acc)
          acc = s
        } else { acc = trial }
      }
      parts.push(acc)
      let off = 0
      for (pi, p) in parts.enumerate() {
        us.push(unit(pi, p.join("\n").trim("\n"), false, off, true, pi < parts.len() - 1))
        off += p.len()
      }
      if has-uses { us.push(unit(parts.len(), "", true, 0, true, false)) }
      }
      }
      // `follow` (a "+" in notebook.toml): print right after the previous snippet.
      if it.at("follow", default: false) and start > 0 {
        let prev = us.at(start - 1)
        let new = us.slice(start)
        if new.len() == 1 and not prev.brk and prev.h + gap + new.at(0).h <= cap {
          let merged = prev
          merged.insert("h", prev.h + gap + new.at(0).h)
          merged.insert("extra", prev.extra + (new.at(0),))
          us = us.slice(0, start - 1) + (merged,)
        } else {
          // Too tall to share a box: keep both strictly in order instead.
          us = us.slice(0, start - 1) + ((..prev, pinned: true),) + new.map(u => (..u, pinned: true))
        }
      }
    }
    units.push(us)
  }

  let cols = ()
  let cur = ((kind: "toc", h: toc-h),)
  let used = toc-h
  for (ci, us) in units.enumerate() {
    let rem = us
    let headed = false
    while rem.len() > 0 {
      let lead = if cur.len() > 0 { gap } else { 0pt }
      if not headed { lead += hdr-h + head-gap }
      let space = col-h - used - lead
      let first = rem.at(0)
      let best = none
      let best-h = 0pt
      // Candidates: the next few snippets after the first one.
      let cand = range(1, rem.len()).filter(i => not rem.at(i).pinned)
      cand = cand.slice(0, calc.min(window - 1, cand.len()))
      if first.pinned or window <= 1 { cand = () }
      let subsets = ((),)
      for i in cand { subsets += subsets.map(s => s + (i,)) }
      let tot-of(s) = s.map(i => rem.at(i).h + gap).sum(default: 0pt)
      if first.h <= space {
        // Take the first snippet, then fill the rest as tightly as possible.
        for s in subsets {
          let tot = first.h + tot-of(s)
          if tot <= space and tot > best-h {
            best = (0,) + s
            best-h = tot
          }
        }
      } else if cur.len() > 0 {
        // The first snippet does not fit here: plug the gap with later ones;
        // the first snippet then opens the next column.
        for s in subsets.filter(s => s.len() > 0) {
          let tot = tot-of(s) - gap
          if tot <= space and tot > best-h {
            best = s
            best-h = tot
          }
        }
      }
      if best == none {
        if cur.len() == 0 {
          best = (0,) // taller than an empty column; overflow rather than loop
          best-h = first.h
        } else {
          cols.push(cur)
          cur = ()
          used = 0pt
          continue
        }
      }
      if not headed {
        cur.push((kind: "chapter", ci: ci, h: hdr-h))
        headed = true
      }
      for i in best { cur.push((kind: "item", ..rem.at(i))) }
      used += lead + best-h
      rem = rem.enumerate().filter(((i, u)) => i not in best).map(((i, u)) => u)
      if cur.last().at("brk", default: false) {
        cols.push(cur)
        cur = ()
        used = 0pt
      }
    }
  }
  if cur.len() > 0 { cols.push(cur) }
  cols
}

// ---------------------------------------------------------------- output

#let render-col(col, labels) = block(width: col-w, height: col-h, {
  for (i, e) in col.enumerate() {
    if i > 0 { v(if col.at(i - 1).kind == "chapter" { head-gap } else { gap }) }
    if e.kind == "toc" { toc(labels) }
    else if e.kind == "chapter" { chapter-head(e.ci) }
    else {
      for (j, u) in ((e,) + e.at("extra", default: ())).enumerate() {
        if j > 0 { v(gap) }
        snippet(chapters.at(u.ci).items.at(u.ii), part: u.part, code: u.code, uses: u.uses, off: u.off)
      }
    }
  }
})

#let col-names(col) = {
  let names = if col.at(0).kind == "toc" { ("Contents",) } else { () }
  for e in col {
    if e.kind != "toc" {
      let n = chapters.at(e.ci).name
      if n not in names { names.push(n) }
    }
  }
  names
}

#let page-header(p, cs, npages) = {
  let cells = ()
  for j in range(3) {
    if j > 0 { cells.push([]) }
    let cell = if j < cs.len() [
      #text(font: mono, weight: "bold", size: 7pt, col-label(3 * p + j)) #h(4pt)
      #text(font: sans, size: 6.5pt, fill: gray, col-names(cs.at(j)).join(" · "))
    ] else []
    // ICPC rule: university and team name top-left, page number top-right.
    if j == 0 {
      cell = [#text(font: sans, weight: "bold", size: 7pt)[#cfg.university · #cfg.team] #h(10pt) #cell]
    }
    if j == 2 {
      cell = [#cell #h(1fr) #text(font: sans, weight: "bold", size: 8pt)[#(p + 1)]]
    }
    cells.push(cell)
  }
  grid(columns: (col-w, gutter, col-w, gutter, col-w), align: left + bottom, ..cells)
  v(2pt)
  line(length: 100%, stroke: 0.4pt)
}

#context {
  let cols = pack()
  let labels = (:)
  for (k, col) in cols.enumerate() {
    for e in col {
      if e.kind == "item" {
        for u in (e,) + e.at("extra", default: ()) {
          if u.part == 0 { labels.insert(str(u.ci) + "-" + str(u.ii), col-label(k)) }
        }
      }
    }
  }
  let npages = calc.ceil(cols.len() / 3)
  let fills = cols.map(c => col-used(c) / col-h)
  let inner = fills.slice(0, calc.max(fills.len() - 1, 1))
  let mn = calc.min(..inner)
  [#metadata((
    pages: npages,
    columns: cols.len(),
    fill: inner.sum() / inner.len(),
    min_fill: mn,
    min_col: col-label(inner.position(f => f == mn)),
  )) <stats>]

  let sep = align(center, line(angle: 90deg, length: col-h, stroke: 0.3pt + luma(190)))
  for p in range(npages) {
    let cs = cols.slice(3 * p, calc.min(3 * p + 3, cols.len()))
    let cells = ()
    for (j, c) in cs.enumerate() {
      if j > 0 { cells.push(sep) }
      cells.push(render-col(c, labels))
    }
    page(header: page-header(p, cs, npages), grid(columns: (col-w, gutter, col-w, gutter, col-w), ..cells))
  }
}
