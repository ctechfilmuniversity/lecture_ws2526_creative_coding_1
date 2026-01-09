<!-- Copilot / AI agent guidance for contributors to this repo -->
# Copilot Instructions — Creative Coding I (CC1)

Purpose
- Help maintain and author course content in `docs/` (Jekyll site). Keep site structure, frontmatter and image references intact.

Big picture (what to know first)
- This repository is a Jekyll/GitHub-Pages style course site. Main content lives in `docs/` and is configured by `docs/_config.yml` (remote_theme: just-the-docs).
- Key folders: `docs/01_sessions/` (weekly session README todo lists), `docs/02_scripts/` (detailed scripts), `docs/03_slides/`, `docs/04_submissions/`.
- Pages use YAML frontmatter (`layout`, `title`, `nav_order`, `parent`, `has_children`). Do not remove or break frontmatter when editing.

Conventions & patterns to follow
- Treat each session folder's `README.md` as the authoritative session todo list; edit content only inside the Markdown body — preserve frontmatter.
- Scripts in `docs/02_scripts/` are long-form Markdown with images in relative paths (e.g. `img/introduction/...`). Keep image locations and alt text intact.
- Submissions: students upload to `docs/04_submissions/<lastname>/<session_index>/`. When adding example submissions, follow that folder pattern.
- Links: prefer relative links within `docs/` so GitHub Pages renders correctly. External resources are allowed but do not inline large binary files into the repo.

Local preview / common workflows
- This site uses a remote theme and standard Jekyll frontmatter. Recommended local preview (requires Ruby + bundler + jekyll):
- `bundle install` && `bundle exec jekyll serve --source docs --config docs/_config.yml`
- If you cannot run Ruby, validate locally by checking Markdown/frontmatter only; do not change theme settings unless necessary.

What Copilot / AI agents can safely do
- Fix grammar, typos or formatting inside Markdown bodies while preserving frontmatter and file paths.
- Add or update small content sections (e.g., expand a script example), create new session skeletons under `docs/01_sessions/` following existing README templates.
- Add missing image references only if the image file is added to the appropriate `img/` folder.

What to avoid / risky changes
- Do not change `docs/_config.yml` or the remote theme without human approval.
- Do not rearrange or rename top-level folders (`01_sessions`, `02_scripts`, `03_slides`, `04_submissions`).
- Avoid large refactors of navigation (`nav_order`, `parent`) — these affect site layout.

Examples (concrete snippets)
- Preserve frontmatter. Example top of a script:
  ```yaml
  ---
  layout: default
  title: Script 01 - Introduction
  parent: Scripts
  nav_order: 1
  ---
  ```
- Session folder pattern: `docs/04_submissions/<lastname>/<session_index>/` (create folders following this pattern when adding example submissions).

If this file already exists
- Merge: preserve any existing guidance blocks (scope, do/don't, local commands). Keep project-specific examples above.

If unsure
- Leave a clear TODO comment in the file and open an issue/PR for a human to review.

Next step
- Ask maintainers whether you should run the Jekyll preview locally (Ruby) or rely on GitHub Pages checks.
