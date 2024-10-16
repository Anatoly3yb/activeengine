#include "editor/editor_translation.h"

#include "core/io/compression.h"
#include "core/io/file_access_memory.h"
#include "core/io/translation_loader_po.h"
#include "editor/doc_translations.gen.h"
#include "editor/editor_translations.gen.h"

Vector<String> get_editor_locales() {
	Vector<String> locales;

	EditorTranslationList *etl = _editor_translations;
	while (etl->data) {
		const String &locale = etl->lang;
		locales.push_back(locale);

		etl++;
	}

	return locales;
}

void load_editor_translations(const String &p_locale) {
	EditorTranslationList *etl = _editor_translations;
	while (etl->data) {
		if (etl->lang == p_locale) {
			Vector<uint8_t> data;
			data.resize(etl->uncomp_size);
			int ret = Compression::decompress(data.ptrw(), etl->uncomp_size, etl->data, etl->comp_size, Compression::MODE_DEFLATE);
			ERR_FAIL_COND_MSG(ret == -1, "Compressed file is corrupt.");

			FileAccessMemory *fa = memnew(FileAccessMemory);
			fa->open_custom(data.ptr(), data.size());

			Ref<Translation> tr = TranslationLoaderPO::load_translation(fa, true);

			if (tr.is_valid()) {
				tr->set_locale(etl->lang);
				TranslationServer::get_singleton()->set_tool_translation(tr);
				break;
			}
		}

		etl++;
	}
}

void load_doc_translations(const String &p_locale) {
	DocTranslationList *dtl = _doc_translations;
	while (dtl->data) {
		if (dtl->lang == p_locale) {
			Vector<uint8_t> data;
			data.resize(dtl->uncomp_size);
			int ret = Compression::decompress(data.ptrw(), dtl->uncomp_size, dtl->data, dtl->comp_size, Compression::MODE_DEFLATE);
			ERR_FAIL_COND_MSG(ret == -1, "Compressed file is corrupt.");

			FileAccessMemory *fa = memnew(FileAccessMemory);
			fa->open_custom(data.ptr(), data.size());

			Ref<Translation> tr = TranslationLoaderPO::load_translation(fa, false);

			if (tr.is_valid()) {
				tr->set_locale(dtl->lang);
				TranslationServer::get_singleton()->set_doc_translation(tr);
				break;
			}
		}

		dtl++;
	}
}
