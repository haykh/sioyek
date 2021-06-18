#pragma once

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <qstandarditemmodel.h>

#include <mupdf/fitz.h>

#include "book.h"
#include "utf8.h"


#define LL_ITER(name, start) for(auto name=start;(name);name=name->next)

std::wstring to_lower(const std::wstring& inp);
void convert_toc_tree(fz_outline* root, std::vector<TocNode*>& output);
void get_flat_toc(const std::vector<TocNode*>& roots, std::vector<std::wstring>& output, std::vector<int>& pages);
int mod(int a, int b);
bool intersects(float range1_start, float range1_end, float range2_start, float range2_end);
void parse_uri(std::string uri, int* page, float* offset_x, float* offset_y);
bool includes_rect(fz_rect includer, fz_rect includee);
char get_symbol(int scancode, bool is_shift_pressed);
//GLuint LoadShaders(filesystem::path vertex_file_path_, filesystem::path fragment_file_path_);

template<typename T>
int argminf(const std::vector<T> &collection, std::function<float(T)> f) {

	float min = std::numeric_limits<float>::infinity();
	int min_index = -1;
	for (int i = 0; i < collection.size(); i++) {
		float element_value = f(collection[i]);
		if (element_value < min){
			min = element_value;
			min_index = i;
		}
	}
	return min_index;
}
void rect_to_quad(fz_rect rect, float quad[8]);
void copy_to_clipboard(const std::wstring& text);
fz_rect corners_to_rect(fz_point corner1, fz_point corner2);
void install_app(char* argv0);
int get_f_key(std::string name);
void show_error_message(std::wstring error_message);
std::wstring utf8_decode(const std::string& encoded_str);
std::string utf8_encode(const std::wstring& decoded_str);
bool is_rtl(int c);
std::wstring reverse_wstring(const std::wstring& inp);
bool parse_search_command(const std::wstring& search_command, int* out_begin, int* out_end, std::wstring* search_text);
QStandardItemModel* get_model_from_toc(const std::vector<TocNode*>& roots);
TocNode* get_toc_node_from_indices(const std::vector<TocNode*>& roots, const std::vector<int>& indices);
fz_stext_char_s* find_closest_char_to_document_point(fz_stext_page* stext_page, fz_point document_point, int* location_index);
void get_stext_block_string(fz_stext_block* block, std::wstring& res);
bool does_stext_block_starts_with_string(fz_stext_block* block, const std::wstring& str);
void simplify_selected_character_rects(std::vector<fz_rect> selected_character_rects, std::vector<fz_rect>& resulting_rects);
void pdf_sandwich_maker(fz_context* context, std::wstring original_file_name, std::wstring sandwich_file_name);
